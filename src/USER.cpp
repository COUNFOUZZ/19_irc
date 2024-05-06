#include "../include/Server.hpp"

void	Server::_user(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	this->_mapSocketAndClients[socket].setUsername(arg[0]);
	this->_mapSocketAndClients[socket].setHostname(arg[2]);
}
