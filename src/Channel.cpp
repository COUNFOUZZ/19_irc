#include "../include/Channel.hpp"


Channel::Channel(void) {
	this->_name = "";
}

Channel::Channel(std::string name) : _name(name) {}

Channel::~Channel(void) {}

/*** Getters ***/

const std::string	Channel::getName() const {
	return (this->_name);
}
