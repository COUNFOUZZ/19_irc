#include "../include/Server.hpp"

bool	Server::_nickAlreadyTaken(std::string& newNick, Client cl) {
	for (size_t i = 0; i < this->_mapSocketAndClients.size(); ++i) {
		if (newNick == this->_mapSocketAndClients[i].getNickname()) {
			cl.sendMessage(ERR_NICKNAMEINUSE(newNick));			
			return true;
		}
	}
	return false;
}

bool Server::_isSpecialChar(std::string& nickname) const {
    const std::string specialChar("-_[]{}|`");

    for (size_t i = 0; i < nickname.size(); ++i) {
        bool isSpecial = false;
        for (size_t j = 0; j < specialChar.size(); ++j) {
            if (nickname[i] == specialChar[j]) {
                isSpecial = true;
                break;
            }
        }
        if (!isalnum(nickname[i]) && !isSpecial)
            return false;
    }
    return true;
}

bool	Server::_isValidNickname(std::string& nickname, Client cl) {
	if (nickname.length() > 9)
		nickname = nickname.substr(0, 9);
	if (nickname.empty() || nickname == "anonymous"
		|| !isalpha(nickname[0]) || !this->_isSpecialChar(nickname)) {
		cl.sendMessage(ERR_ERRONEUSNICKNAME(nickname));
		return false;
	}
	return true;
}

bool	Server::_checkNickname(std::string& nickname, Client cl) {
	return !this->_nickAlreadyTaken(nickname, cl) && this->_isValidNickname(nickname, cl);
}

void	Server::_nick(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	if (!this->_mapSocketAndClients[socket].getPassword().empty()) {
		if (!this->_checkNickname(arg[0], this->_mapSocketAndClients[socket]))
			return;
		if (!this->_mapSocketAndClients[socket].getIsRegistered()) {
			this->_mapSocketAndClients[socket].setNickname(arg[0]);
		} else {
			if (!arg.size())
				return this->_mapSocketAndClients[socket].sendMessage(ERR_NONICKNAMEGIVEN());
			if (this->_mapSocketAndClients[socket].getIsRegistered()) {
				std::string	msg = this->_mapSocketAndClients[socket].getPrefix() + " NICK :" + arg[0] + "\r\n";
				this->_mapSocketAndClients[socket].sendMessage(msg);
			}
			this->_mapSocketAndClients[socket].setNickname(arg[0]);
		}
	}
}
