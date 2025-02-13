#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <sys/socket.h> //socket
#include <fcntl.h> //fcntl
#include <arpa/inet.h> //IPPROTO_TCP
#include <unistd.h> //close

#include "../exception/Exception.hpp"
#include "Kqueue.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

typedef struct s_server_info {
	std::string	name;
	int			sockfd;
	uint32_t	ip; //ip는 config 쪽에서 int로 줌 
	int			port;
	int			que_size;
	int			so_sndbuf;
	int			so_rcvbuf;

} t_server_info;

typedef struct s_accept_info {
	int					sockfd;
	int					http_status;
	struct sockaddr_in	addr;
	// std::string			request_head, requeset_body;
	// std::string			response_head, response_body;
	// t_read_state		read_status;
	time_t				connection_time;
	int					header_buffer_size, body_buffer_size;
	int					response_size;
} t_accept_info;

typedef struct s_session_info {
	std::string	session_id; 
	std::string	user_id;
} t_session_info;

typedef std::map<int, t_accept_info> t_accept_info_map;
typedef std::map<int, HttpMsg> t_request_map;
typedef std::map<int, HttpMsg> t_response_map;

class Server {
	private:
		t_server_info		m_server_info; //서버 정보
		t_accept_info_map	m_accept_info_map; //(accept socket, client info) 
		t_request_map		m_request_msg_map; //(accept socket, request)
		t_response_map		m_response_msg_map; //(accept socket, response)
	public:
						Server(t_server_info info);
		virtual			~Server();
		//socker
		int				getServSocket(uint32_t ip, int port, int que_size);
		//option
		void			setSockOpt(const int& sockfd);
		// uint32_t	ipToInt(const std::string& ip);
		void			setNonBlocking(const int& sockfd);
		//connect
		int				addNewAccept(int server_sockfd);
		void			closeConnection(int sockfd);
		virtual void	sendToClient(int from_sockfd, int to_sockfd) = 0;
		virtual void	sendToServer(int from_sockfd, int to_sockfd) = 0;
		//recv&send
		int				recvBuffer(const int& from_sockfd, const size_t& buffer_size, std::string& request);

		//get
		t_server_info&		getServerInfo();
		t_accept_info&		getAcceptInfo(int accept_sockfd);
		t_accept_info_map&	getAcceptInfoMap();
		HttpMsg&			getRequestMsg(int accept_sockfd);
		HttpMsg&			getResponseMsg(int accept_sockfd);
		//http
};

#endif
