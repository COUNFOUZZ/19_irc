#include "../include/Server.hpp"

void	Server::_mode(int socket, std::vector<std::string>& arg) {
	if (arg.size() < 2)
		return;

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
		case 'i': {
			if (right[0] == '+') {
				if (this->_channels[channelName].getNbrInvited())
					this->_channels[channelName].clearInviteList();
				this->_channels[channelName].setInviteOnly(true);
				this->_channels[channelName].setChannelModes('i');
			} else {
				if (this->_channels[channelName].getNbrInvited())
					this->_channels[channelName].clearInviteList();
				this->_channels[channelName].setInviteOnly(false);
				this->_channels[channelName].delChannelModes('i');
			}
			break;
		}
		case 't': {
			if (right[0] == '+') {
				this->_channels[channelName].setChannelModes('t');
			} else {
				this->_channels[channelName].delChannelModes('t');
			}
			break;
		} case 'k': {
			if (right[0] == '+') {
				if (arg.size() != 3)
					return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "MODE"));
				std::string	password(arg[2]);
				if (password.empty())
					return this->_mapSocketAndClients[socket].sendMessage(ERR_KEYSET(this->_mapSocketAndClients[socket].getNickname(), channelName, "If you set a password, it can't be empty."));
				this->_channels[channelName].setPassword(password);
				this->_channels[channelName].setChannelModes('k');
			} else {
				this->_channels[channelName].setPassword("");
				this->_channels[channelName].delChannelModes('k');
			}
			break;
		} case 'o': {
			if (arg.size() < 3)
                return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "MODE"));
			user = arg[2];
			if (!this->_userExist(user))
				return this->_mapSocketAndClients[socket].sendMessage(ERR_USERNOTINCHANNEL(this->_mapSocketAndClients[socket].getNickname(), channelName, user));
			std::map<int, Client>::iterator	it_user(this->_findClientByNickname(user));
			if (right[0] == '+') {
				it_user->second.addChannelAndRight(channelName, right[1]);
				it_user->second.sendMessage(RPL_YOUREOPER(channelName));
			} else {
				it_user->second.delARightFromChannelAndRight(channelName, right[1]);
			}
			break;
		} case 'l': {
			if (right[0] == '+') {
				if (arg.size() != 3)
					return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "MODE"));
				for (size_t i = 0; i < arg[2].size(); ++i)
					if (!isdigit(arg[2][i]))
						return;
				std::stringstream	ss(arg[2]);
				int					limit;

				ss >> limit;
				if (ss.fail())
					throw std::runtime_error("in mode, stringstream failed.");
				if (limit > 1000) {
					std::cerr << "server cannot limit channel up to 1000 users." << std::endl;
					return;
				}
				this->_channels[channelName].setLimit(limit);
				this->_channels[channelName].setChannelModes('l');
			} else {
				if (arg.size() != 2)
					return this->_mapSocketAndClients[socket].sendMessage(ERR_NEEDMOREPARAMS(this->_mapSocketAndClients[socket].getNickname(), "MODE"));
				this->_channels[channelName].setLimit(0);
				this->_channels[channelName].delChannelModes('l');
			}
			break;
		}
	}
}