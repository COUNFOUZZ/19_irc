#include "../include/Client.hpp"

Client::Client(void) : _socket(-1), _isRegistered(false), _username(""), _nickname("") {}
Client::Client(int socket) : _socket(socket), _isRegistered(false), _username(""), _nickname("") {}
Client::~Client(void) {}

Client&	Client::operator=(const Client& dest) {
	if (this == &dest)
		return *this;
	this->_socket = dest._socket;
	this->_isRegistered = dest._isRegistered;
	this->_username = dest._username;
	this->_nickname = dest._nickname;
	return *this;
}

void	Client::sendMessage(const std::string& message) const
{
	if (send(this->_socket, message.c_str(), message.size(), 0) < 0)
	{
		throw (std::runtime_error("send() in Client::sendMessage"));
	}
}

/*** Setters ***/

void	Client::setUsername(std::string username) {this->_username = username;}
void	Client::setNickname(std::string nickname) {this->_nickname = nickname;}

/*** Getters ***/

bool				Client::getIsRegistered(void) const {return this->_isRegistered;}
const std::string	Client::getUsername(void) const {return this->_username;}
const std::string	Client::getNickname(void) const {return this->_nickname;}
