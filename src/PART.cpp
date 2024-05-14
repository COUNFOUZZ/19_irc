#include "../include/Server.hpp"

void	Server::_part(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	if (arg.size() >= 1) {
		std::string	msg(this->_mapSocketAndClients[socket].getPrefix() + " PART ");
		std::string	buffer;

		for (size_t i = 0; i < arg.size(); ++i)
			buffer += arg[i] + ' ';
		buffer.erase(buffer.size() - 1);
		msg += buffer + "\r\n";
		this->_channels[arg[0]].eraseUserFromChannel(this->_mapSocketAndClients[socket].getNickname());
		this->_channels[arg[0]].broadcast(msg, this->_mapSocketAndClients[socket]);
	}
}