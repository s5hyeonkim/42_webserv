#include <iostream>
#include <stdexcept>

int	main(int argc, char *argv[]) {
    (void)	argc;
    (void)  argv;

    try {
      std::cout << "it is webserv" << std::endl;
    }
    catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
    }
}