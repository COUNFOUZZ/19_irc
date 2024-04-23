#include "../include/Client.hpp"

Client::Client(void) : _socket(-1), _isRegistred(false), _username(""), _nickname("") {}
Client::Client(int socket) : _socket(socket), _isRegistred(false), _username(""), _nickname("") {}
Client::~Client(void) {}

Client&	Client::operator=(const Client& dest) {
	if (this == &dest)
		return *this;
	this->_socket = dest._socket;
	this->_isRegistred = dest._isRegistred;
	this->_username = dest._username;
	this->_nickname = dest._nickname;
	return *this;
}

/*** Setters ***/

void	Client::setUsername(std::string username) {this->_username = username;}
void	Client::setNickname(std::string nickname) {this->_nickname = nickname;}

/*** Getters ***/

bool				Client::getIsRegistred(void) const {return this->_isRegistred;}
const std::string	Client::getUsername(void) const {return this->_username;}
const std::string	Client::getNickname(void) const {return this->_nickname;}
