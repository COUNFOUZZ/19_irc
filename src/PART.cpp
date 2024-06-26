#include "../include/Server.hpp"

void	Server::_part(int socket, std::vector<std::string>& arg) {
	if (arg.size() < 1){
		this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "PART"));
        return;
	}
	if (this->_channels.find(arg[0]) == this->_channels.end()) {
		this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHCHANNEL(this->_mapSocketAndClients[socket].getNickname(), arg[0]));
		return;
	}
	if (!this->_channels[arg[0]].isUserIsInChannel(this->_mapSocketAndClients[socket].getNickname())) {
		this->_mapSocketAndClients[socket].sendMessage(ERR_NOTONCHANNEL(this->_mapSocketAndClients[socket].getNickname(), arg[0]));
		return;
	}
	std::string	msg(this->_mapSocketAndClients[socket].getPrefix() + " PART ");
	std::string	buffer;

	for (size_t i = 0; i < arg.size(); ++i)
		buffer += arg[i] + ' ';
	buffer.erase(buffer.size() - 1);
	msg += buffer + "\r\n";
	this->_channels[arg[0]].delUserFromChannel(this->_mapSocketAndClients[socket].getNickname());
	this->_mapSocketAndClients[socket].delActiveChannel(arg[0]);
	this->_mapSocketAndClients[socket].sendMessage(msg);
	if (this->_channels[arg[0]].getNbrOfClient()) {
		this->_channels[arg[0]].broadcast(msg, this->_mapSocketAndClients[socket]);
	} else {
		this->_mapSocketAndClients[socket].delChannelAndRight(arg[0]);
		this->_channels.erase(arg[0]);
	}
}