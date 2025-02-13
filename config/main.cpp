#include <iostream>
#include <stdexcept>
#include "AppConfig.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int	main(int argc, char *argv[]) {
	std::string	s("localhost:2424");
	// std::string	s("localhost:2424");
	struct sockaddr_in	*ptr2;
	(void) argc;
	(void) argv;
	struct addrinfo *ptr;
	struct addrinfo hints;

    try {
		std::memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		std::cout << s.substr(0, s.find(':')).c_str() << " " << s.substr(s.find(':') + 1).c_str() << std::endl;
		std::cout << getaddrinfo(s.substr(0, s.find(':')).c_str(), s.substr(s.find(':') + 1).c_str(), &hints, &ptr) << std::endl;
		ptr2 = (struct sockaddr_in *)ptr->ai_addr;
		// big -> little
		std::cout << 127 + 256 *256 * 256 * 1 << " " << 2424 % 256 *256 + 2424 / 256 << std::endl;
		std::cout << (unsigned int)(ptr2->sin_addr.s_addr) << " " << ptr2->sin_port << std::endl;
    	// AppConfig	*ptr = AppConfig::getInstance("../utils/conf.d/nginx.conf");

		// std::cout << ptr->getter("localhost", "listen") << std::endl;
      	std::cout << "it is webserv" << std::endl;
    }
    catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
    }
}