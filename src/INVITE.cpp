#include "../include/Server.hpp"

void	Server::_invite(int socket, std::vector<std::string>& arg) {
	if (arg.size() < 2)
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "INVITE"));
	std::string	target, channelName;
	target = arg[0];
	channelName = arg[1];

	if (!this->_userExist(target))
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHNICK(this->_mapSocketAndClients[socket].getNickname()));
	if (this->_channels.find(channelName) != this->_channels.end()) {
		if (!this->_channels[channelName].isUserIsInChannel(this->_mapSocketAndClients[socket].getNickname()))
			return this->_mapSocketAndClients[socket].sendMessage(ERR_NOTONCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));
		if (this->_channels[channelName].isUserIsInChannel(target))
			return this->_mapSocketAndClients[socket].sendMessage(ERR_USERONCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));
		if (this->_channels[channelName].checkAMode('i')) {
			if (!this->_mapSocketAndClients[socket].checkRightFromChannelAndRight(channelName, 'o'))
				return this->_mapSocketAndClients[socket].sendMessage(ERR_CHANOPRIVSNEEDED(this->_mapSocketAndClients[socket].getNickname(), channelName));
		}
		this->_channels[channelName].addNicknameInInviteList(target);
		this->_mapSocketAndClients[socket].sendMessage(RPL_INVITING(this->_mapSocketAndClients[socket].getNickname(), target, channelName));
		std::map<int, Client>::iterator it;
		for (it = this->_mapSocketAndClients.begin(); it != this->_mapSocketAndClients.end(); ++it)
			if (it->second.getNickname() == target)
				break;
		if (it != this->_mapSocketAndClients.end()) {
			std::string	rpl_msg(this->_mapSocketAndClients[socket].getPrefix() + " INVITE " + it->second.getNickname() + " " + channelName + "\r\n");
			it->second.sendMessage(rpl_msg);
		}
	}
}