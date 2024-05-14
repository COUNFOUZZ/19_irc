#include "../include/Channel.hpp"


Channel::Channel(void) : _channelName(""), _topic("") {}
Channel::Channel(std::string channelName) : _channelName(channelName), _topic("") {}
Channel::~Channel(void) {}

/*** Methods ***/
void	Channel::addUser(Client client) {
	this->_client.push_back(client);
}

void	Channel::clientAnnounceHimself(Client client) const {
	for (size_t i = 0; i < this->_client.size(); ++i) {
		std::string	rpl_msg(client.getPrefix() + " JOIN " + ":" + this->getChannelName() + "\r\n");
		this->_client[i].sendMessage(rpl_msg);
	}
}

/*** Setters ***/
void	Channel::setChannelName(std::string channelName) {this->_channelName = channelName;}
void	Channel::setTopic(std::string topic) {this->_topic = topic;}

/*** Getters ***/
const std::string	Channel::getChannelName(void) const {return this->_channelName;}
const std::string	Channel::getTopic(void) const {return this->_topic;}
void				Channel::getListOfUsers(Client client) const {
	std::string	users;

	for (size_t i = 0; i < this->_client.size(); ++i) {
		users += this->_client[i].getNickname();
		if (i != this->_client.size() - 1)
			users += " ";
	}
	client.sendMessage(RPL_NAMREPLY(client.getNickname(), this->getChannelName(), users));
}
