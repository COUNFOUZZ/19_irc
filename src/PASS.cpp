#include "../include/Server.hpp"

int	Server::_whichPassword(std::string pass) {
	if (pass == this->_password)
		return 1;
	else if (pass == OPERATOR_PASSWORD)
		return 2;
	return 0;
}

void	Server::_pass(int socket, std::vector<std::string>& arg) {
	int	check = this->_whichPassword(arg[0]);

	switch (check) {
		case 1:
			this->_mapSocketAndClients[socket].setPassword(arg[0]);
			break;
		case 2:
			this->_mapSocketAndClients[socket].setPassword(arg[0]);
			this->_mapSocketAndClients[socket].setServerOP(true);
			break;
		default:
			this->_mapSocketAndClients[socket].sendMessage(ERR_PASSWDMISMATCH(this->_mapSocketAndClients[socket].getNickname()));
	}
}