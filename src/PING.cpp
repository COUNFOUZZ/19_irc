#include "../include/Server.hpp"

void	Server::_ping(int socket, std::vector<std::string>& arg) {
	this->_mapSocketAndClients[socket].sendMessage(std::string(":") + SERVER_NAME + " PONG " + arg[0] + "\r\n");
}

void	Server::_pong(int socket, std::vector<std::string>& arg) {
	static_cast<void>(socket);
	static_cast<void>(arg);
}
