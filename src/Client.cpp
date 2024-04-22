#include "../include/Client.hpp"

Client::Client(int socket) : _socket(socket), _nickname(""), _username("") {}
Client::~Client(void) {}

/*** Setters ***/

void	Client::setUsername(std::string username) {this->_username = username;}
void	Client::setNickname(std::string nickname) {this->_nickname = nickname;}

/*** Getters ***/

const std::string	Client::getUsername(void) {return (this->_username);}
const std::string	Client::getNickname(void) {return (this->_nickname);}
