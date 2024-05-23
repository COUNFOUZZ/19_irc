#include "../include/Server.hpp"

void	Server::_topic(int socket, std::vector<std::string>& arg) {
	if (arg.size() < 1)
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "TOPIC"));
	std::string	channelName(arg[0]);

	if (this->_channels.find(channelName) == this->_channels.end())
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));
	if (arg.size() == 1) {
		if (!this->_channels[channelName].getTopic().empty())
			return this->_mapSocketAndClients[socket].sendMessage(RPL_TOPIC(this->_mapSocketAndClients[socket].getNickname(), channelName, this->_channels[channelName].getTopic()));
		else
			return this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(this->_mapSocketAndClients[socket].getNickname(), channelName));
	}
	if (this->_channels[channelName].checkAMode('t') && !this->_channels[channelName].isInOpVector(this->_mapSocketAndClients[socket].getNickname()))
		return this->_mapSocketAndClients[socket].sendMessage(ERR_CHANOPRIVSNEEDED(this->_mapSocketAndClients[socket].getNickname(), channelName));
	std::string	topic("");

	for (size_t i = 1; i < arg.size(); ++i) {
		topic += arg[i];
		if (i != arg.size() - 1)
			topic += " ";
	}
	if (topic[0] == ':')
		topic.erase(0,1);
	std::string	rpl_msg(this->_mapSocketAndClients[socket].getPrefix() + " TOPIC " + channelName + " :" + topic + "\r\n");

	this->_channels[channelName].setTopic(topic);
	this->_mapSocketAndClients[socket].sendMessage(rpl_msg);
	this->_channels[channelName].broadcast(rpl_msg, this->_mapSocketAndClients[socket]);
}
