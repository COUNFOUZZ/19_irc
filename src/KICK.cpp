#include "../include/Server.hpp"

void	Server::_kick(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	if (arg.size() < 2)
		this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS("KICK"));
	std::string channelName, userToKick, reason;

	channelName = arg[0];
	userToKick = arg[1];
	if (this->_channels.find(channelName) == this->_channels.end()) {
		this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));
		return;
	}
	if (!this->_channels[channelName].isUserIsInChannel(userToKick)) {
		this->_mapSocketAndClients[socket].sendMessage(ERR_USERNOTINCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName, userToKick));
		return;
	}
	if (!this->_mapSocketAndClients[socket].checkRightFromChannelAndRight(channelName, 'o')) {
		this->_mapSocketAndClients[socket].sendMessage(ERR_CHANOPRIVSNEEDED(this->_mapSocketAndClients[socket].getNickname(), channelName));
		return;
	}
	if (arg.size() > 2) {
		for (size_t i = 2; i < arg.size(); ++i) {
			reason += arg[i];
			if (i != arg.size() - 1)
				reason += " ";
		}
	}
	reason += "\r\n";
	std::string	rpl_msg(this->_mapSocketAndClients[socket].getPrefix() + " KICK " + channelName + " " + userToKick + " " + reason);
	this->_mapSocketAndClients[socket].sendMessage(rpl_msg);
	this->_channels[channelName].delUserFromChannel(userToKick);
	this->_channels[channelName].broadcast(rpl_msg, this->_mapSocketAndClients[socket]);
}