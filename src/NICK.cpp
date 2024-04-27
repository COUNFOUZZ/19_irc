#include "../include/Server.hpp"

bool	Server::_nickAlreadyTaken(std::string newNick, Client cl) {
	std::map<std::string, Client>::const_iterator it;
	for (it = this->_mapNicknameAndClients.begin(); it != this->_mapNicknameAndClients.end(); it++) {
		if (newNick == it->first) {
			cl.sendMessage(ERR_NICKNAMEINUSE(newNick));			
			return true;
		}
	}
	return false;
}

bool	Server::_isValidNickname(std::string nickname, Client cl) {
	if (nickname.length() > 9 || nickname == "anonymous") {	// Need to check if "anonymous" is entered in uppercase or different letter with upper and lower case ?
		cl.sendMessage(ERR_ERRONEUSNICKNAME());
		return false;
	}
	return true;
}

bool	Server::_checkNickname(std::string nickname, Client cl) {
	return !this->_nickAlreadyTaken(nickname, cl) && this->_isValidNickname(nickname, cl);
}

void	Server::_nick(int socket, std::vector<std::string>& arg, Client cl) {
	if (!cl.getIsRegistered()) {
		if (!this->_checkNickname(arg[0], cl))
			return ;
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
