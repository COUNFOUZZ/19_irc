#include "../include/Server.hpp"

void	Server::_join(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	std::cout << "JOIN CMD TRIGGERED" << std::endl;

	std::string channelName = arg[0];
	if (arg.size() < 1)
		return (this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS("JOIN")));

	//First : create the channel if it doesnt exist yet
	if (this->_channels.find(channelName) == this->_channels.end()) {
		this->_channels[channelName] = Channel(channelName);
		this->_channels[channelName].addUser(this->_mapSocketAndClients[socket]);
		std::string rpl_msg(this->_mapSocketAndClients[socket].getPrefix() + " JOIN " + channelName + "\r\n");
		this->_mapSocketAndClients[socket].sendMessage(rpl_msg);
		this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(channelName));
	} else {
		this->_channels[channelName].clientAnnounceHimself(this->_mapSocketAndClients[socket]);
		this->_channels[channelName].addUser(this->_mapSocketAndClients[socket]);
		if (this->_channels[channelName].getTopic().empty())
			this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(channelName));
		else
			this->_mapSocketAndClients[socket].sendMessage(RPL_TOPIC(this->_mapSocketAndClients[socket].getNickname(), channelName, this->_channels[channelName].getTopic()));
	}
}
