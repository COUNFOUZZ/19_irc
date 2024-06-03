#include "../include/Server.hpp"

void	Server::_privmsg(int socket, std::vector<std::string>& arg) {
	if (arg[0][0] != '#' && arg[0][0] != '&' && arg[0][0] != '!' && arg[0][0] != '+') {
		if (!this->_userExist(arg[0])) {
			this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHNICK(this->_mapSocketAndClients[socket].getNickname(), ""));
			return;
		}
		Client	target;

		for (size_t i = 0; i < this->_mapSocketAndClients.size(); ++i) {
			if (this->_mapSocketAndClients[i].getNickname() == arg[0]) {
				target = this->_mapSocketAndClients[i];
				break;
			}
		}
		if (!target.getIsRegistered()) {
			this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHNICK(arg[0], ""));
			return;
		}
			std::string	msg(this->_mapSocketAndClients[socket].getPrefix() + " PRIVMSG " + target.getNickname() + " ");
			std::string	buffer;

			for (size_t i = 1; i < arg.size(); ++i)
				buffer += arg[i] + ' ';
			buffer.erase(buffer.size() - 1);
			msg += buffer + "\r\n";
			target.sendMessage(msg);
	} else {
		if (this->_channels.find(arg[0]) == this->_channels.end()) {
			this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHCHANNEL(this->_mapSocketAndClients[socket].getNickname(), arg[0]));
			return;
		}
		Channel				target;

		for (std::map<std::string, Channel>::iterator	it = this->_channels.begin(); it != this->_channels.end(); ++it) {
			if (it->first == arg[0]) {
				target = this->_channels[it->first];
				break;
			}
		}
		if (target.isUserIsInChannel(this->_mapSocketAndClients[socket].getNickname())) {
			std::string msg(this->_mapSocketAndClients[socket].getPrefix() + " PRIVMSG " + target.getChannelName() + " ");
			std::string buffer;
			for (size_t i = 1; i < arg.size(); ++i)
					buffer += arg[i] + ' ';
			buffer.erase(buffer.size() - 1);
			msg += buffer + "\r\n";
			target.broadcast(msg, this->_mapSocketAndClients[socket]);
		}
	}
}