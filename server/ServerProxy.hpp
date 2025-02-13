#ifndef SERVERPROXY_HPP
# define SERVERPROXY_HPP

# include "Server.hpp"

class ServerProxy : public Server {
	private:
		std::map<int, t_server_info> m_connect_info;
	public:
		ServerProxy(t_server_info info);
		~ServerProxy();
		int				addNewConnect(t_server_info info);
		void			sendToClient(int from_sockfd, int to_sockfd);
		void			sendToServer(int from_sockfd, int to_sockfd);
		t_server_info&	getConnectInfo(int connect_sockfd);
};

#endif
