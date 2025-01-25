#include <iostream>
#include <stdexcept>
#include "Config.hpp"

int	main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;

    try {
    	Config	cf("../utils/conf.d/nginx.conf");
      	std::cout << "it is webserv" << std::endl;
    }
    catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
    }
}