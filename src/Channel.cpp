#include "../include/Channel.hpp"


Channel::Channel(void) : _channelName(""), _topic(""), _channelModes("") {}
Channel::Channel(std::string channelName) : _channelName(channelName), _topic(""), _channelModes("") {}
Channel::~Channel(void) {}

/*** Methods ***/
void	Channel::addUser(Client& client) {
	if (client.getServerOP() && !this->_isInOpVector(client.getNickname()))
		this->addOperator(client.getNickname());
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

bool	Channel::_isInOpVector(std::string nickname) const {
	for (std::vector<std::string>::const_iterator it = this->_operators.begin(); it != this->_operators.end(); ++it)
		if (*it == nickname)
			return true;
	return false;
}

void	Channel::addOperator(std::string nickname) {
	this->_operators.push_back(nickname);
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

void				Channel::rplNameAndEnd(Client client) const {
	std::string	users;

	for (size_t i = 0; i < this->_clients.size(); ++i) {
		if (this->_isInOpVector(this->_clients[i].getNickname()))
			users += '@';
		users += this->_clients[i].getNickname();
		if (i != this->_clients.size() - 1)
			users += " ";
	}
	client.sendMessage(RPL_NAMREPLY(client.getNickname(), this->getChannelName(), users));
	client.sendMessage(RPL_ENDOFNAMES(this->getChannelName(), client.getNickname()));
}

/*** Setters ***/
void	Channel::setChannelName(std::string channelName) {this->_channelName = channelName;}
void	Channel::setTopic(std::string topic) {this->_topic = topic;}
void	Channel::setChannelModes(char mode) {
	if (this->_channelModes.find(mode) == this->_channelModes.npos)
		this->_channelModes += mode;
}
void	Channel::delChannelModes(char mode) {
	if (this->_channelModes.find(mode) != this->_channelModes.npos)
		this->_channelModes.erase(std::remove(this->_channelModes.begin(), this->_channelModes.end(), mode));
}

/*** Getters ***/
const std::string	Channel::getChannelName(void) const {return this->_channelName;}
const std::string	Channel::getTopic(void) const {return this->_topic;}
const std::string	Channel::getChannelModes(void) const {return this->_channelModes;}
std::vector<Client>	Channel::getClients(void) const {return this->_clients;}
size_t				Channel::getNbrOfClient(void) const {return this->_clients.size();}