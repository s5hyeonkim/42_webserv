#include "ServerProxy.hpp"

#define REQUEST_SIZE 10000
#define RESPONSE_SIZE 10000

ServerProxy::ServerProxy(t_server_info info) : Server(info) {

}

ServerProxy::~ServerProxy() {
	
}

int	ServerProxy::addNewConnect(t_server_info info) {
	int	server_fd;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		Exception::handleSystemError(errno);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(info.port);
	addr.sin_addr.s_addr = info.ip;
	if (connect(server_fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1)
	{
		close(server_fd);
		Exception::handleSystemError(errno);
	}
	setNonBlocking(server_fd);
	info.sockfd = server_fd;
	m_connect_info[server_fd] = info;
	// std::cout << "ip: " << info.ip << std::endl;
	// std::cout << "port: " << info.port << std::endl;
	std::cout << "add New Connect :" << server_fd << std::endl; 
	return (server_fd);
}

void ServerProxy::sendToClient(int from_sockfd, int to_sockfd) {
	char	buffer[RESPONSE_SIZE];
	std::string response;
	int		bytes, bytes2;

	bytes2 = 0;
	while ((bytes = recv(from_sockfd, buffer, sizeof(buffer), 0)) > 0){
		buffer[bytes] = '\0';
		response += buffer;
		bytes2 += bytes; 
	}
	if (bytes2 <= 0)
	{
		closeConnection(from_sockfd);
		return ;
	}
	std::cout << "# ProxysendToClient" << std::endl;
	// std::cout << sizeof(response) << std::endl;
	// std::cout << response << std::endl;
	send(to_sockfd, response.c_str(), bytes2, 0);
	closeConnection(to_sockfd);
}

int recvFromClient(int from_sockfd, size_t buffer_size, std::string &request, int &http_status) {
	int	bytes_line, bytes_lines;

	// header와 body사이즈 만큼 읽어오기
	char		buffer[buffer_size];
	// bytes_lines = recvBuffer(from_sockfd, buffer_size, request);
	bytes_lines = 0;
	while ((bytes_line = recv(from_sockfd, buffer, buffer_size, 0)) > 0) {
		buffer[bytes_line] = '\0';
		request += buffer;
		bytes_lines += bytes_line;
	}
	if (bytes_lines < 0) {
		http_status = HttpMsg::getHttpStatusCode(); // > 응답처리할 때 해당 상태코드 전달 하는 방식으로 처리한다.
		return (1);
	}
	return (0);
}

void ServerProxy::sendToServer(int from_sockfd, int to_sockfd) {
	t_accept_info	info;
	std::string		request, line;

	std::cout << "# ProxysendToWeb" << std::endl;
	// 해당 fd의 클라이언트 정보 & request 정보 받아오기 (config)
	info = getAcceptInfo(from_sockfd);
	/* 읽어오기 */
	if (recvFromClient(from_sockfd, info.header_buffer_size + info.body_buffer_size, request, info.http_status))
		return ;
	
	// /* 유효성 검사 - buffer size  > request_msg에 저장*/
	// HttpMsg			request_msg;

	// request_msg = getRequestMsg(from_sockfd);

	// // 헤더가 있는지 검사 > 헤더 크기 조건 유효성 검사 > 헤더에 저장
	// if (request_msg.getReadStatus() == READ_LINE) {
	// 	// line 파싱 & 유효성 검사
	// 	// request_msg.setRequestLine()
	// 	// line을 모두 읽었다면 read_status 갱신 
	// }
	// if (request_msg.getReadStatus() == READ_HEAD) { // 헤더를 읽는 중이라면
	// 	// 헤더 파싱 & 유효성 검사

	// 	// 헤더를 모두 읽었다면 read_status 갱신 
	// }
	// // 바디가 있는지 검사 > 바디 크기 조건 유효성 검사 > 바디에 저장
	// if (request_msg.getReadStatus() == READ_BODY) { // 바디를 읽는 중이라면 
	// 	// 바디 파싱 & 유효성 검사

	// 	// 바디를 모두 읽었다면 read_status 갱신 
	// }
	

	std::cout << "request size:" << request.size() << std::endl;
	// std::cout << request << std::endl;
	send(to_sockfd, request.c_str(), request.size(), 0);

}

t_server_info& ServerProxy::getConnectInfo(int connect_sockfd) {
	return (m_connect_info[connect_sockfd]);
}


