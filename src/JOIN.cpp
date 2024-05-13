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
		std::cout << "Channel name: " << this->_channels[channelName].getName() << std::endl;
		this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(channelName));
	}

	//Second : Join channel if exists
}
