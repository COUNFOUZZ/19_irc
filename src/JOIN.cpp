#include "../include/Server.hpp"

void	Server::_join(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(socket);
	static_cast<void>(arg);
	static_cast<void>(cl);
	std::cout << "JOIN CMD TRIGGERED" << std::endl;


	std::string channelName = arg[0];
	if (arg.size() < 1)
		return (this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS("JOIN")));


	//First : create the channel if it doesnt exist yet
	if (_channels.find(channelName) == _channels.end()) {
		this->_channels[channelName] = Channel(channelName);
		std::cout << "Channel name: " << this->_channels[channelName].getName() << std::endl;
		_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(channelName));
	}

	//Second : Join channel if exists
}
