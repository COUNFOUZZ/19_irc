#include "../include/Channel.hpp"


Channel::Channel(void)
{
	this->_name = "";
	return ;
}

Channel::Channel(std::string name) : _name(name)
{
	return ;
}

Channel::~Channel(void) {}

/*** Getters ***/

const std::string	Channel::getName() const
{
	return (this->_name);
}
