#include "../include/Server.hpp"

bool	Server::_isValidCharChannel(std::string channelName) const {
    const std::string specialChar("-_.");

	channelName.erase(0);	// delete first character (# || &)
	for (size_t i = 0; i < channelName.size(); ++i) {
		bool isSpecialChar = false;
		for (size_t j = 0; j < specialChar.size(); ++j) {
			if (channelName[i] == specialChar[j]) {
				isSpecialChar = true;
				break;
			}
			if (!isalnum(channelName[i]) && !isSpecialChar)
				return false;
		}
	}
	return true;
}

bool	Server::_isValidChannel(std::string channelName) const {
	if (channelName.size() < 2 || channelName.size() > 50
		|| (channelName[0] != '#' && channelName[0] != '&' && channelName[0] != '!' && channelName[0] != '+')
		|| !this->_isValidCharChannel(channelName))
		return false;
	return true;
}

void	Server::_join(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	std::string channelName;
	if (arg.size() < 1)
		return (this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS("JOIN")));

	for (size_t i = 0; i < arg.size(); ++i) {
		channelName = arg[i];
		if (!this->_isValidChannel(channelName)) {
			this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));
			continue;
		}
		if (this->_channels.find(channelName) == this->_channels.end()) {
			this->_channels[channelName] = Channel(channelName);
			this->_channels[channelName].addUser(this->_mapSocketAndClients[socket]);
			this->_channels[channelName].addOperator(this->_mapSocketAndClients[socket].getNickname());
			std::string rpl_msg(this->_mapSocketAndClients[socket].getPrefix() + " JOIN " + channelName + "\r\n");
			this->_mapSocketAndClients[socket].sendMessage(rpl_msg);
			this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(channelName));
			this->_channels[channelName].rplNameAndEnd(this->_mapSocketAndClients[socket]);
		} else {
			if (this->_channels[channelName].isUserIsInChannel(this->_mapSocketAndClients[socket].getNickname()))
				return;
			if (this->_channels[channelName].getTopic().empty())
				this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(channelName));
			else
				this->_mapSocketAndClients[socket].sendMessage(RPL_TOPIC(this->_mapSocketAndClients[socket].getNickname(), channelName, this->_channels[channelName].getTopic()));
			this->_channels[channelName].addUser(this->_mapSocketAndClients[socket]);
			this->_channels[channelName].printOperator();
			this->_channels[channelName].clientAnnounceHimself(this->_mapSocketAndClients[socket]);
			this->_channels[channelName].rplNameAndEnd(this->_mapSocketAndClients[socket]);
		}
	}
}
