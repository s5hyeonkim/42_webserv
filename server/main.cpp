#include <iostream>
#include <stdexcept>
#include "ServerManager.hpp"

int	main(int argc, char *argv[]) {
	(void)	argc;
	(void)  argv;

	try {
		ServerManager	server_manager;
		server_manager.runServer();
		std::cout << "it is webserv" << std::endl;
		//프로그램 꺼야 되는 거면 
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}