#include "Server.hpp"

#define EVENT_CNT 100
#define REQUEST_SIZE 10000
#define RESPONSE_SIZE 10000


Server::Server(t_server_info info) : m_server_info(info) {
	m_server_info.sockfd = getServSocket(m_server_info.ip, m_server_info.port, m_server_info.que_size);
	std::cout << "new server socket:" << m_server_info.sockfd << std::endl;
	// Kqueue::addEvent(m_server_info.sockfd, EVFILT_READ, EV_ADD);
}

Server::~Server() { 
	// m_clients_addr;
}

int Server::getServSocket(uint32_t ip, int port, int que_size) {
	int					sockfd;
	struct sockaddr_in	addr;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == -1)
		Exception::handleSystemError(errno);
	setSockOpt(sockfd);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = ip;
	if (bind(sockfd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1)
		Exception::handleSystemError(errno);
	if (listen(sockfd, que_size) == -1)
		Exception::handleSystemError(errno);
	setNonBlocking(sockfd);
	return (sockfd);
}

void Server::setSockOpt(const int& sockfd) {
	int	reuse, snd_buf, rcv_buf, state;

	reuse = 1, snd_buf = RESPONSE_SIZE, rcv_buf = REQUEST_SIZE;
	state = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if (!state)
		state = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf));
	if (!state)
		state = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, sizeof(rcv_buf));
	if (state)
		Exception::handleSystemError(errno);
}

// 함수 구현해야함
// uint32_t Server::ipToInt(const std::string& ip) {
// 	uint32_t ret;

// 	inet_pton(AF_INET, ip.c_str(), &ret);
// 	return (ret);
// }

void Server::setNonBlocking(const int& sockfd) {
	int	flag;

	flag = fcntl(sockfd, F_GETFL, 0);
	if (flag == -1)
		Exception::handleSystemError(errno);
	if (fcntl(sockfd, F_SETFL, flag | O_NONBLOCK) == -1)
		Exception::handleSystemError(errno);
}

t_accept_info	getNewAcceptInfo() {
	t_accept_info info;
	
	// info.sockfd = ;
	info.header_buffer_size = 1000;
	info.body_buffer_size = 10000;
	info.connection_time = 20;
	// info.response_size = ;
	// info.http_status = 0;
	// info.read_status = READ_REQ_LINE;
	return (info);
}

int Server::addNewAccept(int server_sockfd) {
	t_accept_info		info;
	socklen_t			accept_addr_len;
	int					accept_socket;

	info = getNewAcceptInfo();
	accept_addr_len = sizeof(info.addr.sin_addr);
	accept_socket = accept(server_sockfd, reinterpret_cast<struct sockaddr *>(&info.addr.sin_addr), &accept_addr_len);
	if (accept_socket == -1)
		Exception::handleSystemError(errno); // system error ? 아니면 현재 동작만 error 처리 ? 
	setSockOpt(accept_socket);
	setNonBlocking(accept_socket);
	std::cout << "new accept socket:" << accept_socket << std::endl;
	m_accept_info_map[accept_socket] = info;
	return (accept_socket);
}

// int Server::addNewServer(uint32_t server_ip, int server_port) {
// 	int server_sockfd;

// 	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
// 	if (server_sockfd == -1)
// 		Exception::handleSystemError(errno);
// 	struct sockaddr_in addr;
// 	addr.sin_family = AF_INET;
// 	addr.sin_port = htons(server_port);
// 	addr.sin_addr.s_addr = server_ip;
// 	if (connect(server_sockfd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1) {
// 		close(server_sockfd);
// 		Exception::handleSystemError(errno);
// 	}
// 	setNonBlocking(server_sockfd);
// 	return (server_sockfd);
// }

void Server::closeConnection(int sockfd) {
	(void) sockfd;
}

int	Server::recvBuffer(const int& from_sockfd, const size_t& buffer_size, std::string& request) {
	char		buffer[buffer_size];
	int			bytes_line, bytes_lines;

	bytes_lines = 0;
	while ((bytes_line = recv(from_sockfd, buffer, buffer_size, 0)) > 0) {
		buffer[bytes_line] = '\0';
		request += buffer;
		bytes_lines += bytes_line;
	}
	return (bytes_lines);
}

t_accept_info& Server::getAcceptInfo(int accept_sockfd) {
	return (m_accept_info_map[accept_sockfd]);
}

t_accept_info_map& Server::getAcceptInfoMap() {
	return (m_accept_info_map);
}

t_server_info& Server::getServerInfo() {
	return (m_server_info);
}

HttpMsg& Server::getRequestMsg(int accept_sockfd) {
	return (m_request_msg_map[accept_sockfd]);
}

HttpMsg& Server::getResponseMsg(int accept_sockfd) {
	return (m_response_msg_map[accept_sockfd]);
}

