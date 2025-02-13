#ifndef SERVERMANAGER_HPP
# define SERVERMANAGER_HPP

# include "ServerWeb.hpp"
# include "ServerProxy.hpp"

class ServerManager {
	private:
		int			kq;
		int			proxy_fd, ptow_fd, wtop_fd;
		ServerProxy	proxy;
		ServerWeb	web;
	public:
					ServerManager();
					~ServerManager();
		void		runServer();
		void		handleEvent();
};

#endif