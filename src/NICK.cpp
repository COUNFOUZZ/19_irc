#include "../include/Server.hpp"

void	Server::_nick(int socket, std::vector<std::string>& arg, Client cl) {
	std::string	newNick;

	if (!cl.getIsRegistred()) {
		std::stringstream	ss;
		std::string			socketNbr;
		ss << socket;
		if (ss.fail())
			throw std::runtime_error("stringstream failed !");
		ss >> socketNbr;
		newNick = arg[0] + socketNbr;
		this->_mapSocketAndClients[socket].setNickname(newNick);
		this->_mapNicknameAndClients[newNick] = this->_mapSocketAndClients[socket];
	} else {
		
	}
}