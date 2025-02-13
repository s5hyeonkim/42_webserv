#ifndef SERVERWEB_HPP
# define SERVERWEB_HPP

# include "Server.hpp"

class ServerWeb : public Server {
	private:
		std::string	m_name, m_root; //서버명, 정적파일 경로,
	public:
		ServerWeb(t_server_info info);
		~ServerWeb();
		void	sendToClient(int from_sockfd, int to_sockfd);
		void	sendToServer(int from_sockfd, int to_sockfd);
	
};


#endif
