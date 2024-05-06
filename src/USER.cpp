#include "../include/Server.hpp"

void	Server::_user(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	if (arg.size() != 4) {
		this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS("Invalid USER command !"));
		return;
	}
	this->_mapSocketAndClients[socket].setUsername(arg[0]);
	this->_mapSocketAndClients[socket].setHostname(arg[1]);
}
