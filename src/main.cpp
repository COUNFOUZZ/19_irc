#include "../include/Server.hpp"

bool	g_shutdown = false;

static void	shutdown(int) {
	g_shutdown = true;
}

int	main(int argc, char **argv) {
	if (argc != 3) {
		return std::cerr << "Invalid number of arguments (./ircserv <port> <password>)" << std::endl, 1;
	}

	signal(SIGINT, shutdown);
	signal(SIGTSTP, SIG_IGN);
	try {
		Server	server(argv[1], argv[2]);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
