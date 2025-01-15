#include <iostream>
#include <stdexcept>
#include "MainServer.hpp"

int	main(int argc, char *argv[]) {
    (void)	argc;

    try {
		MainServer m(argv[1]);
    }
    catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
    }
}