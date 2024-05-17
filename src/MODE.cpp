#include "../include/Server.hpp"

void	Server::_mode(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);

	if (arg.size() == 3) {
		std::string	channelName, right, user;
		channelName = arg[0];
		right = arg[1];
		user = arg[2];

		std::cout << "debug cmd: " << std::endl << "arg[0] = " << channelName << std::endl
												<< "arg[1] = " << right << std::endl
												<< "arg[2] = " << user << std::endl;

		if (!channelName.empty() && this->_userExist(user)) {
			if (this->_channels.find(channelName) != this->_channels.end() && (this->_mapSocketAndClients[socket].getServerOP() || this->_channels[channelName].isInOpVector(this->_mapSocketAndClients[socket].getNickname()))) {
				std::map<int, Client>::iterator it;
				for (it = this->_mapSocketAndClients.begin(); it != this->_mapSocketAndClients.end(); ++it)
					if (it->second.getNickname() == user)
						break;
				switch (right[0]) {
					case '+':
						std::cout << "+ TRIGGERED with right: " << right << std::endl;
						right.erase(0, 1);
						std::cout << "right after erase: " << right << std::endl;
						for (size_t	i = 0; i < right.size(); ++i)
							it->second.addChannelAndRight(channelName, right[i]);
						break;
					case '-':
						std::cout << "- TRIGGERED" << std::endl;
						right.erase(0, 1);
						for (size_t	i = 0; i < right.size(); ++i)
							it->second.delARightFromChannelAndRight(channelName, right[i]);
						break;
					default:
						std::cout << "error" << std::endl;
				}
				std::cout << "USER: " << it->second.getNickname() << " [" << it->second.getRightFromChannel(channelName) << "]" << std::endl;
			}
		}
	}
}
