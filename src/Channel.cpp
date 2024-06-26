#include "../include/Channel.hpp"


Channel::Channel(void) : _channelName(""), _topic(""), _channelModes("") {}
Channel::Channel(std::string channelName) : _channelName(channelName), _topic(""), _channelModes(""), _password(""), _limit(0), _inviteOnly(false) {}
Channel::~Channel(void) {}

/*** Methods ***/
void	Channel::addUser(Client& client) {
	if ((client.getServerOP() && !this->isInOpVector(client.getNickname()))
	|| (!this->getNbrOfClient() && !this->isInOpVector(client.getNickname()))
	|| (client.checkRightFromChannelAndRight(this->getChannelName(), 'o') && !this->isInOpVector(client.getNickname()))) {
		this->addOperator(client.getNickname());
		if (!client.checkRightFromChannelAndRight(this->getChannelName(), '0'))
			client.addChannelAndRight(this->getChannelName(), 'o');
	} else {
		client.addChannelAndRight(this->getChannelName(), '\0');
	}
	this->_clients.push_back(client);
	client.addActiveChannel(this->getChannelName());
}

void	Channel::broadcast(std::string message, Client cl) const {
	for (size_t i = 0; i < this->_clients.size(); ++i) {
		if (this->_clients[i].getNickname() != cl.getNickname())
			this->_clients[i].sendMessage(message);
	}
}

void	Channel::clientAnnounceHimself(Client client) const {
	for (size_t i = 0; i < this->_clients.size(); ++i) {
		std::string	rpl_msg(client.getPrefix() + " JOIN " + this->getChannelName() + "\r\n");
		this->_clients[i].sendMessage(rpl_msg);
	}
}

bool	Channel::isUserIsInChannel(std::string nickname) const {
	for (std::vector<Client>::const_iterator it = this->_clients.begin(); it < this->_clients.end(); ++it)
		if (it->getNickname() == nickname)
			return true;
	return false;
}

bool	Channel::isInOpVector(std::string nickname) const {
	for (std::vector<std::string>::const_iterator it = this->_operators.begin(); it != this->_operators.end(); ++it)
		if (*it == nickname)
			return true;
	return false;
}

void	Channel::addOperator(std::string nickname) {
	if (!nickname.empty())
		this->_operators.push_back(nickname);
}

void Channel::delOperator(std::string nickname) {
	if (!nickname.empty()) {
		std::vector<std::string>::iterator it = std::find(this->_operators.begin(), this->_operators.end(), nickname);
		if (it != this->_operators.end())
			this->_operators.erase(it);
	}
}

void	Channel::eraseUserFromChannel(Client& client) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it < this->_clients.end(); ++it) {
		if (it->getNickname() == client.getNickname()) {
			this->_clients.erase(it);
			client.delActiveChannel(this->getChannelName());
			return;
		}
	}
}

void	Channel::printOperator(void) const {
	std::cout << "OPERATORS:";
	for (size_t i = 0; i < this->_operators.size(); ++i)
		std::cout << " " + this->_operators[i];
	std::cout << std::endl;
}

void	Channel::_refreshAllUsersList(std::string users) const {
	for (size_t i = 0; i < this->_clients.size(); ++i) {
		this->_clients[i].sendMessage(RPL_NAMREPLY(this->_clients[i].getNickname(), this->getChannelName(), users));
		// this->_clients[i].sendMessage(RPL_ENDOFNAMES(this->getChannelName(), this->_clients[i].getNickname())); // in comment because if it's uncomment, when an op come in the chan all user see the message who is in the channel.
	}
}

void	Channel::rplNameAndEnd(Client client) const {
	std::string	users;

	for (size_t i = 0; i < this->_clients.size(); ++i) {
		if (this->isInOpVector(this->_clients[i].getNickname()))
			users += '@';
		users += this->_clients[i].getNickname();
		if (i != this->_clients.size() - 1)
			users += " ";
	}
	if (client.checkRightFromChannelAndRight(this->getChannelName(), 'o')) {
		this->_refreshAllUsersList(users);
	}
	else {
		client.sendMessage(RPL_NAMREPLY(client.getNickname(), this->getChannelName(), users));
		client.sendMessage(RPL_ENDOFNAMES(this->getChannelName(), client.getNickname()));
	}
}

void	Channel::delUserFromChannel(std::string nickname) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it < this->_clients.end(); ++it) {
		if (it->getNickname() == nickname) {
			this->_clients.erase(it);
			// it->delActiveChannel(this->getChannelName());
			return;
		}
	}
}

void	Channel::setChannelModes(char mode) {
	if (this->_channelModes.find(mode) == this->_channelModes.npos)
		this->_channelModes += mode;
}
void	Channel::delChannelModes(char mode) {
	if (this->_channelModes.find(mode) != this->_channelModes.npos)
		this->_channelModes.erase(std::remove(this->_channelModes.begin(), this->_channelModes.end(), mode));
}

bool	Channel::checkAMode(char mode) const {
	for (size_t i = 0; i < this->_channelModes.size(); ++i)
		if (this->_channelModes[i] == mode)
			return true;
	return false;
}

void	Channel::addNicknameInInviteList(std::string nickname) {
	this->_inviteList.push_back(nickname);
}

void	Channel::delNicknameInInviteList(std::string nickname) {
	if (!nickname.empty()) {
		std::vector<std::string>::iterator it = std::find(this->_inviteList.begin(), this->_inviteList.end(), nickname);
		if (it != this->_inviteList.end())
			this->_inviteList.erase(it);
	}
}

void	Channel::clearInviteList(void) {
	this->_inviteList.clear();
}

bool	Channel::checkIsInvited(std::string nickname) const {
	for (size_t i = 0; i < this->_inviteList.size(); ++i)
		if (this->_inviteList[i] == nickname)
			return true;
	return false;
}

/*** Setters ***/
void	Channel::setChannelName(std::string channelName) {this->_channelName = channelName;}
void	Channel::setTopic(std::string topic) {this->_topic = topic;}
void	Channel::setPassword(std::string password) {this->_password = password;}
void	Channel::setLimit(int limit) {this->_limit = limit;}
void	Channel::setInviteOnly(bool value) {this->_inviteOnly = value;}

/*** Getters ***/
const std::string	Channel::getChannelName(void) const {return this->_channelName;}
const std::string	Channel::getTopic(void) const {return this->_topic;}
const std::string	Channel::getChannelModes(void) const {return this->_channelModes;}
std::vector<Client>	Channel::getClients(void) {return this->_clients;}
size_t				Channel::getNbrOfClient(void) const {return this->_clients.size();}
std::string			Channel::getPassword(void) const {return this->_password;}
int					Channel::getLimit(void) const {return this->_limit;}
size_t				Channel::getNbrInvited(void) const {return this->_inviteList.size();}