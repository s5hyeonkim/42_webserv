#include <iostream>
#include <stdexcept>
#include "Server.hpp"

int	main(int argc, char *argv[]) {
	(void)	argc;
	(void)  argv;

	try {
		Server server;
		server.runServ();
		std::cout << "it is webserv" << std::endl;
		//프로그램 꺼야 되는 거면 
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}