#include "Server.hpp"

#define IP "127.0.0.1"
#define PROXY_PORT 2424
#define WEB_PORT 4242
#define QUE_SIZE 20
#define EVENT_CNT 100
#define REQUEST_SIZE 10000
#define RESPONSE_SIZE 10000

Server::Server(){
	kq = Kqueue::getInstance()->getKqueue();
	proxy_fd = getServSocket(IP, PROXY_PORT, QUE_SIZE);
	web_fd = getServSocket(IP, WEB_PORT, QUE_SIZE);
	std::cout << "proxyfd:" <<  proxy_fd << std::endl;
	std::cout << "webfd:" <<  web_fd << std::endl;
	addEvent(proxy_fd, EVFILT_READ, EV_ADD);
	addEvent(web_fd, EVFILT_READ, EV_ADD);
}

Server::~Server() {}

void Server::setNonBlocking(int fd) {
	int	flag;

	flag = fcntl(fd, F_GETFL, 0);
	if (flag == -1)
		Exception::handleSystemError(errno);
	if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1)
		Exception::handleSystemError(errno);
}

void Server::setSockOpt(int fd)
{
	int	reuse,snd_buf, rcv_buf, state;

	reuse = 1, snd_buf = RESPONSE_SIZE, rcv_buf = REQUEST_SIZE;
	state = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if (!state)
		state = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf));
	if (!state)
		state = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, sizeof(rcv_buf));
	if (state)
		Exception::handleSystemError(errno);
}

int Server::getServSocket(std::string ip, int port, int que_size) {
	int					fd;
	struct sockaddr_in	addr;

	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == -1)
		Exception::handleSystemError(errno);
	setSockOpt(fd);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton(ip.c_str(), &addr.sin_addr);
	if (bind(fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1)
		Exception::handleSystemError(errno);
	if (listen(fd, que_size) == -1)
		Exception::handleSystemError(errno);
	setNonBlocking(fd);
	return (fd);
}

void Server::addEvent(int fd, int filter, int flags) {
	struct kevent event;

	EV_SET(&event, fd, filter, flags, 0, 0, NULL);
	if (kevent(kq, &event, 1, NULL, 0, NULL) == -1)
		Exception::handleSystemError(errno);
}

void Server::removeEvent(int fd, int filter)
{
	struct kevent event;

	EV_SET(&event, fd, filter, EV_DELETE, 0, 0, NULL);
	if (kevent(kq, &event, 1, NULL, 0, NULL) == -1)
		Exception::handleSystemError(errno);
}

void Server::runServ()
{
	while (true)
	{
		handleEvent();
		std::cout << "#####################" << std::endl;
	}
}

void Server::handleEvent()
{
	struct kevent	events[EVENT_CNT];
	int				active_n, idx, now_fd, serv_fd;
	
	active_n = kevent(kq, NULL, 0, events, EVENT_CNT, NULL);
	std::cout << "active_n:" << active_n << std::endl;
	for (idx = 0; idx < active_n; idx++) {
		now_fd = events[idx].ident;
		std::cout << "nowfd:" <<  now_fd << std::endl;
		std::cout << "aisempty:" << accept_key.empty() << std::endl;
		std::cout << "cisempty:" << connect_key.empty() << std::endl;
		if (now_fd == proxy_fd)
		{
			std::cout << "#prox" << std::endl;
			accept_key[addNewClientSocket(proxy_fd)] = now_fd;
		}
		else if (now_fd == web_fd)
		{
			std::cout << "#web" << std::endl;
			addNewClientSocket(web_fd); //accept 8
		}
		else if (accept_key[now_fd] == proxy_fd) { 
			serv_fd = openConnection();
			if (serv_fd != -1) {
				accept_key[now_fd] = serv_fd;
				connect_key[serv_fd] = now_fd;
				std::cout << "newservsocket:" << serv_fd << std::endl;
				sendClientRequest(now_fd, serv_fd);
			}
		else
			closeConnection(now_fd);
		}
		else if (accept_key[connect_key[now_fd]] == now_fd) //proxy to client: 현재 fd가 proxy의 connect fd일 때 
		{
			sendProxyReponse(now_fd, connect_key[now_fd]);
		}	
		else // web to proxy - recv 8, send 8 
			sendWebResponse(now_fd);	
	}
}

int Server::openConnection() {
	int serv_fd;

	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_fd == -1)
		Exception::handleSystemError(errno);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(WEB_PORT);
	inet_pton(AF_INET, IP, &addr.sin_addr);
	if (connect(serv_fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1)
	{
		close(serv_fd);
		Exception::handleSystemError(errno);
	}
	setNonBlocking(serv_fd);
	return (serv_fd);
}

int Server::addNewClientSocket(int serv_fd) {
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_len;
	int					client_fd;

	client_addr_len = sizeof(client_addr);
	client_fd = accept(serv_fd, reinterpret_cast<struct sockaddr *>(&client_addr), &client_addr_len);
	if (client_fd == -1)
		Exception::handleSystemError(errno);
	setNonBlocking(client_fd);
	addEvent(client_fd, EVFILT_READ, EV_ADD);
	std::cout << "newclientsocket:" << client_fd << std::endl;
	return (client_fd);
}

void Server::closeConnection(int fd) {
	int connect_fd, accept_fd;

	if (accept_key.find(fd) != accept_key.end())
	{
		connect_fd = accept_key[fd];
		accept_key.erase(fd);
		accept_fd = connect_key[connect_fd];
		connect_key.erase(connect_fd);
		std::cout << "a:close: " << connect_fd << " " << accept_fd << std::endl;

	}
	else if (connect_key.find(fd) != connect_key.end())
	{
		accept_fd = connect_key[fd];
		connect_key.erase(fd);
		connect_fd = accept_key[accept_fd];
		accept_key.erase(accept_fd);
		std::cout << "c:close: " << connect_fd << " " << accept_fd << std::endl;
	}
	removeEvent(connect_fd, EVFILT_READ);
	close (connect_fd);
	removeEvent(accept_fd, EVFILT_READ);
	close (accept_fd);
}

void Server::sendClientRequest(int client_fd, int server_fd) {
	char	request[REQUEST_SIZE];
	int		bytes;

	bytes = recv(client_fd, request, sizeof(request), 0);
	if (bytes <= 0)
		closeConnection(client_fd);
	request[bytes] = '\0';
	send(server_fd, request, bytes, 0);
	std::cout << "=========ClientRequest=========" << std::endl;
	// std::cout << client_fd << " send "  << server_fd << std::endl;
	// std::cout << "=========================" << std::endl;
	// std::cout << request << std::endl;
	// std::cout << "-------------------------" << std::endl;
	addEvent(server_fd, EVFILT_READ, EV_ADD);
}

std::string create_http_response(const std::string &body) {
	/* header */
	std::string response = "HTTP/1.1 200 OK\r\n"; //http 버전, 요청이 성공적으로 처리 됨
	response += "Content-Type: text/html\r\n"; //응답 본문의 데이터가 html의 형식임을 알림 
	response += "Content-Length: " + std::to_string(body.size()) + "\r\n"; //응답 본문의 바이트 크기를 지정
	response += "Connection: keep-alive\r\n\r\n"; // 서버가 응답 후 소켓 연결을 닫을 것을 알림 
	/* body */
	response += body; //html 콘텐츠가 포함된 본문을 헤더 뒤에 추가 
	return (response);
}

void Server::sendProxyReponse(int client_fd, int server_fd)
{
	char	response[RESPONSE_SIZE];
	int		bytes;
	bytes = recv(client_fd, response, sizeof(response), 0);
	if (bytes <= 0)
		closeConnection(client_fd);
	response[bytes] = '\0';
	std::cout << "=========ProxyReponse=========" << std::endl;
	// std::cout << sizeof(response) << std::endl;
	// std::cout << response << std::endl;
	send(server_fd, response, bytes, 0);
	closeConnection(server_fd);
}

void Server::sendWebResponse(int client_fd) {
	char	request[REQUEST_SIZE];
	int		bytes;

	bytes = recv(client_fd, request, REQUEST_SIZE, 0);
	if (bytes <= 0)
		closeConnection(client_fd);
	request[bytes] = '\0';
	std::cout << "=========WebResponse=========" << std::endl;
	// std::cout << client_fd << " send "  << client_fd << std::endl;
	// std::cout << "=========================" << std::endl;
	std::cout << request << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::ifstream	input("html/index.html");
	if (!input)
	{
		closeConnection(client_fd);
		Exception::handleSystemError(errno);
	}
	std::stringstream buffer;
	buffer << input.rdbuf();  // 파일 내용을 한번에 읽어오기
	std::string body = buffer.str();
	// std::string body = "<html><body><h1>This is Webserv</h1></body></html>";
	std::string response = create_http_response(body);
	// std::cout << response << std::endl;
	send(client_fd, response.c_str(), response.size(), 0);
	removeEvent(client_fd, EVFILT_READ);
	// close(client_fd);
}

void validRequeset() {
	//HTTP1.1 이 아니면 

	//Expect: 100-continue 가 포함되어 있지 않다면 
	
}

