#include "../include/Server.hpp"

void	Server::_pass(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	if (arg[0] == this->_password)
		this->_mapSocketAndClients[socket].setPassword(arg[0]);
	else
		this->_mapSocketAndClients[socket].sendMessage(ERR_PASSWDMISMATCH());
}