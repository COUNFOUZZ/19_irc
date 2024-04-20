#include "../include/Server.hpp"

int	main(int argc, char **argv) {
	if (argc != 3) {
		return std::cerr << "Invalid number of arguments (./ircserv <port> <password>)" << std::endl, 1;
	}

	// signal handling here

	try {
		Server	server(argv[1], argv[2]);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}