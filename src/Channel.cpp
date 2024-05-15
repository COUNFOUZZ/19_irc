#include "../include/Channel.hpp"


Channel::Channel(void) : _channelName(""), _topic(""), _channelModes("") {}
Channel::Channel(std::string channelName) : _channelName(channelName), _topic(""), _channelModes("") {}
Channel::~Channel(void) {}

/*** Methods ***/
void	Channel::addUser(Client client) {
	this->_clients.push_back(client);
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
	for (std::vector<Client>::const_iterator it = this->_clients.begin(); it < this->_clients.end(); ++it) {
		if (it->getNickname() == nickname)
			return true;
	}
	return false;
}

void	Channel::eraseUserFromChannel(std::string nickname) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it < this->_clients.end(); ++it) {
		if (it->getNickname() == nickname) {
			this->_clients.erase(it);
			return;
		}
	}
}

/*** Setters ***/
void	Channel::setChannelName(std::string channelName) {this->_channelName = channelName;}
void	Channel::setTopic(std::string topic) {this->_topic = topic;}
void	Channel::setChannelModes(std::string mode) {this->_channelModes.append(mode);}

/*** Getters ***/
const std::string	Channel::getChannelName(void) const {return this->_channelName;}
const std::string	Channel::getTopic(void) const {return this->_topic;}
const std::string	Channel::getChannelModes(void) const {return this->_channelModes;}
std::vector<Client>	Channel::getClients(void) const {return this->_clients;}
void				Channel::getListOfUsers(Client client) const {
	std::string	users;

	for (size_t i = 0; i < this->_clients.size(); ++i) {
		users += this->_clients[i].getNickname();
		if (i != this->_clients.size() - 1)
			users += " ";
	}
	client.sendMessage(RPL_NAMREPLY(client.getNickname(), this->getChannelName(), users));
}
