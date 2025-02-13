#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <iostream> //std::cout
// #include <stdio.h>
#include <stdexcept> //std::runtime_error
#include <fcntl.h> //fcntl
#include <arpa/inet.h>

#include <sys/time.h>
#include <sys/event.h>
#include <sys/types.h>
#include <map>
#include <vector>
#include <unistd.h>

#include "Kqueue.hpp"
#include "../exception/Exception.hpp"

#include <fstream>
#include <sstream>
#include <string>

class Server {
	private:
		int					kq, proxy_fd, web_fd;
		std::map<int, int>	accept_key, connect_key;
		int					time;
	public:
				Server();
				~Server();
		int		getServSocket(std::string ip, int port, int que_size);
		void	setNonBlocking(int fd);
		void	addEvent(int fd, int filter, int flags);
		void	removeEvent(int fd, int filter);
		int		addNewClientSocket(int fd);
		void	runServ();
		void	handleEvent();
		void	sendClientRequest(int client_fd, int server_fd);
		void	sendWebResponse(int client_fd);
		void	sendProxyReponse(int client_fd, int server_fd);
		int		openConnection();
		void	closeConnection(int fd);
		void	setSockOpt(int fd);
};


#endif 