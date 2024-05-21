#include "../include/Server.hpp"

// void	Server::_mode(int socket, std::vector<std::string>& arg, Client cl) {
// 	static_cast<void>(cl);
// 	if (arg.size() == 2 || arg.size() == 3) {
// 		std::string	channelName, right, user;

// 		channelName = arg[0];
// 		right = arg[1];
// 		user = arg[2];
// 		if (!channelName.empty() && this->_userExist(user)) {
// 			if (this->_channels.find(channelName) != this->_channels.end() && (this->_mapSocketAndClients[socket].getServerOP() || this->_channels[channelName].isInOpVector(this->_mapSocketAndClients[socket].getNickname()))) {
// 				std::map<int, Client>::iterator it;
// 				for (it = this->_mapSocketAndClients.begin(); it != this->_mapSocketAndClients.end(); ++it)
// 					if (it->second.getNickname() == user)
// 						break;
// 				switch (right[0]) {
// 					case '+':
// 						right.erase(0, 1);
// 						for (size_t	i = 0; i < right.size(); ++i) {
// 							if (right[i] != 'o') {
// 								this->_mapSocketAndClients[socket].sendMessage(ERR_UNKNOWNMODE(this->_mapSocketAndClients[socket].getNickname(), channelName, right[i]));
// 								continue;
// 							}
// 							it->second.addChannelAndRight(channelName, right[i]);
// 							it->second.sendMessage(RPL_YOUREOPER(channelName));
// 						}
// 						break;
// 					case '-':
// 						right.erase(0, 1);
// 						for (size_t	i = 0; i < right.size(); ++i) {
// 							if (right[i] != 'o') {
// 								this->_mapSocketAndClients[socket].sendMessage(ERR_UNKNOWNMODE(this->_mapSocketAndClients[socket].getNickname(), channelName, right[i]));
// 								continue;
// 							}
// 							it->second.delARightFromChannelAndRight(channelName, right[i]);
// 						}
// 						break;
// 				}
// 				std::cout << "USER: " << it->second.getNickname() << " [" << it->second.getRightFromChannel(channelName) << "]" << std::endl;
// 			}
// 		}
// 	}
// }


void	Server::_mode(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	if (arg.size() < 2)
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS("MODE"));

	std::string	channelName;
	channelName = arg[0];
	if (this->_channels.find(channelName) == this->_channels.end())
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));

	std::vector<Client>				clientList;
	std::vector<Client>::iterator	it;
	clientList = this->_channels[channelName].getClients();
	for (it = clientList.begin(); it != clientList.end(); ++it)
		if (it->getNickname() == this->_mapSocketAndClients[socket].getNickname())
			break;
	if (it == clientList.end())
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NOTONCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName));
	if (!this->_mapSocketAndClients[socket].checkRightFromChannelAndRight(channelName, 'o'))
		return this->_mapSocketAndClients[socket].sendMessage(ERR_CHANOPRIVSNEEDED(this->_mapSocketAndClients[socket].getNickname(), channelName));
	std::string	right;
	right = arg[1];
	if (right.length() > 2)
		return this->_mapSocketAndClients[socket].sendMessage(ERR_UMODEUNKNOWNFLAG(this->_mapSocketAndClients[socket].getNickname(), "Only one flag is allowed for each mode command."));
	if (right[0] != '+' && right[0] != '-')
		return this->_mapSocketAndClients[socket].sendMessage(ERR_UNKNOWNMODE(this->_mapSocketAndClients[socket].getNickname(), channelName, right[0]));
	if (right[1] != 'i' && right[1] != 't' && right[1] != 'k' && right[1] != 'o' && right[1] != 'l')
		return this->_mapSocketAndClients[socket].sendMessage(ERR_UNKNOWNMODE(this->_mapSocketAndClients[socket].getNickname(), channelName, right[1]));
	std::string	user;
	switch (right[1]) {
		// case 'i':
		// 	if (right[0] == '+') {
			
		// 	} else {

		// 	}
		// 	break;
		// case 't':
		// 	if (right[0] == '+') {

		// 	} else {
				
		// 	}
		// 	break;
		// case 'k':
		// 	if (right[0] == '+') {

		// 	} else {
				
		// 	}
		// 	break;
		case 'o':
			if (arg.size() < 3)
                return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS("MODE"));
			user = arg[2];
			if (!this->_userExist(user))
				return this->_mapSocketAndClients[socket].sendMessage(ERR_USERNOTINCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName, user));
			std::map<int, Client>::iterator	it = this->_findClientByNickname(user);
			if (right[0] == '+') {
				it->second.addChannelAndRight(channelName, right[1]);
				it->second.sendMessage(RPL_YOUREOPER(channelName));
			} else {
				it->second.delARightFromChannelAndRight(channelName, right[1]);
			}
			break;
		// case 'l':
		// 	if (right[0] == '+') {

		// 	} else {
				
		// 	}
		// 	break;
	}
}