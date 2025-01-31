#include <iostream>
#include <stdexcept>
#include "Configs.hpp"

int	main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;

    try {
    	Configs::getInstance("../utils/conf.d/nginx.conf");
      	std::cout << "it is webserv" << std::endl;
    }
    catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
    }
}