#include "../include/Server.hpp"

void	Server::_join(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(socket);
	static_cast<void>(arg);
	static_cast<void>(cl);
	std::cout << "JOIN CMD TRIGGERED" << std::endl;
}