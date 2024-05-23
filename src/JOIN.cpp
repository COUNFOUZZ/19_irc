#include "../include/Server.hpp"

bool	Server::_isValidCharChannel(std::string channelName) const {
    const std::string specialChar("-_.");

	channelName.erase(0, 1);	// delete first character (# || &)
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

void	Server::_join(int socket, std::vector<std::string>& arg) {
	if (arg.size() < 1)
		return (this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "JOIN")));

	std::vector<std::string>	channels, passwords;
	std::stringstream					ss(arg[0]);
	std::string							element;
	while (std::getline(ss, element, ','))
		channels.push_back(element);
	ss.clear();
	ss.str(arg[1]);
	while (std::getline(ss, element, ','))
		passwords.push_back(element);
	if (passwords.size() > channels.size())
		return;
	for (size_t i = 0; i < channels.size(); ++i) {
		std::string	channelName(channels[i]);
		std::string	password;
		password.clear();
		if (!passwords[i].empty())
			password = passwords[i];
		if (!this->_isValidChannel(channelName)) {
			this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));
			continue;
		}
		if (this->_channels.find(channelName) == this->_channels.end()) {
			this->_channels[channelName] = Channel(channelName);
			this->_channels[channelName].addUser(this->_mapSocketAndClients[socket]);
			std::string rpl_msg(this->_mapSocketAndClients[socket].getPrefix() + " JOIN " + channelName + "\r\n");
			this->_mapSocketAndClients[socket].sendMessage(rpl_msg);
			this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(this->_mapSocketAndClients[socket].getNickname(), channelName));
			this->_channels[channelName].rplNameAndEnd(this->_mapSocketAndClients[socket]);
		} else {
			if (this->_channels[channelName].checkAMode('l') && this->_channels[channelName].getLimit() != 0 && static_cast<int>(this->_channels[channelName].getNbrOfClient()) >= this->_channels[channelName].getLimit())
				return this->_mapSocketAndClients[socket].sendMessage(ERR_CHANNELISFULL(this->_mapSocketAndClients[socket].getNickname(), channelName));
			if (this->_channels[channelName].checkAMode('k') && this->_channels[channelName].getPassword() != password && !this->_channels[channelName].checkIsInvited(this->_mapSocketAndClients[socket].getNickname()))
				return this->_mapSocketAndClients[socket].sendMessage(ERR_BADCHANNELKEY(this->_mapSocketAndClients[socket].getNickname(), channelName));
			if (this->_channels[channelName].checkAMode('i') && !this->_channels[channelName].checkIsInvited(this->_mapSocketAndClients[socket].getNickname()))
				return this->_mapSocketAndClients[socket].sendMessage(ERR_INVITEONLYCHAN(this->_mapSocketAndClients[socket].getNickname(), channelName));
			if (this->_channels[channelName].isUserIsInChannel(this->_mapSocketAndClients[socket].getNickname()))
				return;
			this->_channels[channelName].addUser(this->_mapSocketAndClients[socket]);
			if (this->_channels[channelName].getTopic().empty())
				this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(this->_mapSocketAndClients[socket].getNickname(), channelName));
			else
				this->_mapSocketAndClients[socket].sendMessage(RPL_TOPIC(this->_mapSocketAndClients[socket].getNickname(), channelName, this->_channels[channelName].getTopic()));
			this->_channels[channelName].printOperator();
			this->_channels[channelName].clientAnnounceHimself(this->_mapSocketAndClients[socket]);
			this->_channels[channelName].rplNameAndEnd(this->_mapSocketAndClients[socket]);
		}
	}
}
