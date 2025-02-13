#include "ServerWeb.hpp"

#define REQUEST_SIZE 10000
#define RESPONSE_SIZE 10000

ServerWeb::ServerWeb(t_server_info info) : Server(info) {

}

ServerWeb::~ServerWeb() {
	
}

#include <fstream>
#include <sstream>
#include <string>
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

void ServerWeb::sendToClient(int from_sockfd, int to_sockfd) {
	char	buffer[REQUEST_SIZE];
	std::string request; 
	int		bytes, bytes2;

	bytes2 = 0;
	while ((bytes = recv(from_sockfd, buffer, sizeof(buffer), 0)) > 0){
		buffer[bytes] = '\0';
		request += buffer; 
		bytes2 += bytes;
	}
	if (bytes2 <= 0)
	{
		closeConnection(from_sockfd);
		return ;
	}
	std::cout << "# WebsendToProxy" << std::endl;
	// std::cout << from_sockfd << " send "  << from_sockfd << std::endl;
	// std::cout << "=========================" << std::endl;
	// std::cout << request << std::endl;
	// std::cout << "-------------------------" << std::endl;
	std::ifstream	input("html/index.html");
	if (!input)
	{
		closeConnection(from_sockfd);
		Exception::handleSystemError(errno);
	}
	std::stringstream buffer2;
	buffer2 << input.rdbuf();  // 파일 내용을 한번에 읽어오기
	// std::string body = buffer.str();
	std::string body = "<html><body><h1>This is Webserv</h1></body></html>";
	std::string response = create_http_response(body);
	std::cout << response << std::endl;
	std::cout << response.size() << std::endl;
	std::cout << to_sockfd << std::endl;
	ssize_t bytes_sent = send(to_sockfd, response.c_str(), response.size(), 0);
	if (bytes_sent == -1) {
		std::cout <<"ERROR" << std::endl;
	} else {
		std::cout << "Sent " << bytes_sent << " bytes to ptow_fd" << std::endl;
	}
	// close(from_sockfd);
}

void ServerWeb::sendToServer(int from_sockfd, int to_sockfd) { (void) from_sockfd, (void) to_sockfd; }
