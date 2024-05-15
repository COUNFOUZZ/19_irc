#include "../include/Client.hpp"

Client::Client(void) : _socket(-1), _isRegistered(false), _username(""), _nickname(""), _realname(""), _hostname(""), _password(""), _userModes("") {}
Client::Client(int socket) : _socket(socket), _isRegistered(false), _username(""), _nickname(""), _realname(""), _hostname(""), _password(""), _userModes("") {}
Client::~Client(void) {}

Client&	Client::operator=(const Client& dest) {
	if (this == &dest)
		return *this;
	this->_socket = dest._socket;
	this->_isRegistered = dest._isRegistered;
	this->_username = dest._username;
	this->_nickname = dest._nickname;
	this->_realname = dest._realname;
	this->_hostname = dest._hostname;
	this->_password = dest._password;
	this->_userModes = dest._userModes;
	return *this;
}

void	Client::sendMessage(const std::string& message) const
{
	if (send(this->_socket, message.c_str(), message.size(), 0) < 0)
		throw (std::runtime_error("send() in Client::sendMessage"));
}

bool	Client::isReadyToBeRegister(void) const {
	return !this->_nickname.empty() && !this->_username.empty();
}

/*** Setters ***/

void	Client::setIsRegistered(bool value) {this->_isRegistered = value;}
void	Client::setUsername(std::string username) {this->_username = username;}
void	Client::setNickname(std::string nickname) {this->_nickname = nickname;}
void	Client::setRealname(std::string realname) {this->_realname = realname;}
void	Client::setHostname(std::string hostname) {this->_hostname = hostname;}
void	Client::setPassword(std::string password) {this->_password = password;}
void	Client::setUserModes(std::string mode) {this->_userModes.append(mode);}
void	Client::delUserModes(char mode) {
	while (this->_userModes.find(mode) != this->_userModes.npos)
		this->_userModes.erase(std::remove(this->_userModes.begin(), this->_userModes.end(), mode));
}

/*** Getters ***/

bool			Client::getIsRegistered(void) const {return this->_isRegistered;}
const std::string	Client::getUsername(void) const {return this->_username;}
const std::string	Client::getNickname(void) const {return this->_nickname;}
const std::string	Client::getRealname(void) const {return this->_realname;}
const std::string	Client::getHostname(void) const {return this->_hostname;}
const std::string	Client::getPassword(void) const {return this->_password;}
const std::string	Client::getPrefix(void) const {return (":" + this->getNickname() + "!" + this->getUsername() + "@" + this->getHostname());}
const std::string	Client::getUserModes(void) const {return this->_userModes;}
