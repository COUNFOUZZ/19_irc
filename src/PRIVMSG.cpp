#include "../include/Server.hpp"

void	Server::_privmsg(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	Client	target;

	for (size_t i = 0; i < this->_mapSocketAndClients.size(); ++i) {
		if (this->_mapSocketAndClients[i].getNickname() == arg[0]) {
			target = this->_mapSocketAndClients[i];
			break;
		}
	}
	if (!target.getIsRegistered()) {
		this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHNICK(arg[0]));
		return;
	}
		std::string	msg(":" + this->_mapSocketAndClients[socket].getNickname() + "!" + this->_mapSocketAndClients[socket].getUsername() + "@" + this->_mapSocketAndClients[socket].getHostname() + " PRIVMSG " + target.getNickname() + " ");
		std::string	buffer;

		for (size_t i = 1; i < arg.size(); ++i)
			buffer += arg[i] + ' ';
		buffer.erase(buffer.size() - 1);
		msg += buffer + "\r\n";
		target.sendMessage(msg);
}