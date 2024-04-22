#include "../include/Client.hpp"

Client::Client(void)
{
	return ;
}

Client::Client(int socket) : _socket(socket)
{
	this->_nickname = "";
	this->_username = "";
	return ;
}

Client::~Client(void)
{
	return ;
}

/*** Setters ***/

void	Client::setUsername(std::string username)
{
	this->_username = username;
	return ;
}

void	Client::setNickname(std::string nickname)
{
	this->_nickname = nickname;
	return ;
}

/*** Getters ***/

const std::string	Client::getUsername(void)
{
	return (this->_username);
}

const std::string	Client::getNickname(void)
{
	return (this->_nickname);
}
