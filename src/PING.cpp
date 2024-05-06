#include "../include/Server.hpp"

void	Server::_ping(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	this->_mapSocketAndClients[socket].sendMessage(std::string(":") + SERVER_NAME + " PONG " + arg[0] + "\r\n");
}