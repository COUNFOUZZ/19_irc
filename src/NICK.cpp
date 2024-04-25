#include "../include/Server.hpp"

void	Server::_checkIfNickAlreadyTaken(std::string newNick, Client cl) {
	std::map<std::string, Client>::iterator it;
	for (it = this->_mapNicknameAndClients.begin(); it != this->_mapNicknameAndClients.end(); it++) {
		if (newNick == it->first)
			cl.sendMessage(ERR_NICKNAMEINUSE(newNick));			
	}
}

void	Server::_nick(int socket, std::vector<std::string>& arg, Client cl) {
	if (!cl.getIsRegistered()) {
		this->_checkIfNickAlreadyTaken(arg[0], cl);
		std::stringstream	ss;
		std::string			socketNbr;
		ss << socket;
		if (ss.fail())
			throw std::runtime_error("stringstream failed !");
		ss >> socketNbr;
		this->_mapSocketAndClients[socket].setNickname(arg[0]);
		this->_mapNicknameAndClients[arg[0]] = this->_mapSocketAndClients[socket];
	} else {
	}
}
