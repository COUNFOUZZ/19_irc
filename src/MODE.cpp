#include "../include/Server.hpp"

void	Server::_mode(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	if (arg.size() == 2 || arg.size() == 3) {
		std::string	channelName, right, user;

		channelName = arg[0];
		right = arg[1];
		user = arg[2];
		if (!channelName.empty() && this->_userExist(user)) {
			if (this->_channels.find(channelName) != this->_channels.end() && (this->_mapSocketAndClients[socket].getServerOP() || this->_channels[channelName].isInOpVector(this->_mapSocketAndClients[socket].getNickname()))) {
				std::map<int, Client>::iterator it;
				for (it = this->_mapSocketAndClients.begin(); it != this->_mapSocketAndClients.end(); ++it)
					if (it->second.getNickname() == user)
						break;
				switch (right[0]) {
					case '+':
						right.erase(0, 1);
						for (size_t	i = 0; i < right.size(); ++i) {
							if (right[i] != 'o') {
								this->_mapSocketAndClients[socket].sendMessage(ERR_UNKNOWNMODE(this->_mapSocketAndClients[socket].getNickname(), channelName, right[i]));
								continue;
							}
							it->second.addChannelAndRight(channelName, right[i]);
							it->second.sendMessage(RPL_YOUREOPER(channelName));
						}
						break;
					case '-':
						right.erase(0, 1);
						for (size_t	i = 0; i < right.size(); ++i) {
							if (right[i] != 'o') {
								this->_mapSocketAndClients[socket].sendMessage(ERR_UNKNOWNMODE(this->_mapSocketAndClients[socket].getNickname(), channelName, right[i]));
								continue;
							}
							it->second.delARightFromChannelAndRight(channelName, right[i]);
						}
						break;
				}
				std::cout << "USER: " << it->second.getNickname() << " [" << it->second.getRightFromChannel(channelName) << "]" << std::endl;
			}
		}
	}
}
