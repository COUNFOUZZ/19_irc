#include "../include/Client.hpp"

Client::Client(void) : _socket(-1), _isRegistered(false), _username(""), _nickname(""), _realname(""), _hostname(""), _password(""), _userModes(""), _serverOP(false) {}
Client::Client(int socket) : _socket(socket), _isRegistered(false), _username(""), _nickname(""), _realname(""), _hostname(""), _password(""), _userModes(""), _serverOP(false) {}
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
	this->_serverOP = dest._serverOP;
	this->_activeChannels = dest._activeChannels;
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

void	Client::delUserModes(char mode) {
	if (this->_userModes.find(mode) != this->_userModes.npos)
		this->_userModes.erase(std::remove(this->_userModes.begin(), this->_userModes.end(), mode));
}

void Client::addActiveChannel(const std::string channelName) {
	if (!channelName.empty())
		this->_activeChannels.push_back(channelName);
}

bool Client::isInChannel(const std::string channelName) const {
	if (channelName.empty() || this->_activeChannels.empty())
		return false;
	for (std::vector<std::string>::const_iterator it = this->_activeChannels.begin(); it != this->_activeChannels.end(); ++it)
		if (*it == channelName)
			return true;
	return false;
}

void Client::delActiveChannel(const std::string channelName) {
	if (!channelName.empty() && this->isInChannel(channelName)) {
		std::vector<std::string>::iterator it = this->_giveIteratorActiveChannel(channelName);
		if (it != this->_activeChannels.end())
			this->_activeChannels.erase(it);
	}
}

std::vector<std::string>::iterator	Client::_giveIteratorActiveChannel(std::string channelName) {
	for (std::vector<std::string>::iterator	it = this->_activeChannels.begin(); it != this->_activeChannels.end(); ++it)
		if (*it == channelName)
			return it;
	return this->_activeChannels.end();
}

size_t	Client::nbrOfActiveChannel(void) const {
	return this->_activeChannels.size();
}

/*** Channel/right ***/
void	Client::addChannelAndRight(std::string channelName, char mode) {
	if (channelName.empty())
		return;
	std::map<std::string, std::string>::iterator it = this->_channelAndRight.find(channelName);

	if (it != this->_channelAndRight.end()) {
		if (it->second.find(mode) == it->second.npos)
			it->second.push_back(mode);
	} else {
		std::string	strMode;
		if (mode)
			strMode.push_back(mode);
		this->_channelAndRight.insert(std::pair<std::string, std::string>(channelName, strMode));
	}
}

void	Client::delARightFromChannelAndRight(std::string channelName, char mode) {
	if (channelName.empty() || !mode)
		return;
	std::map<std::string, std::string>::iterator it = this->_channelAndRight.find(channelName);

	if (it != this->_channelAndRight.end()) {
		if (it->second.find(mode) != it->second.npos)
			it->second.erase(it->second.find(mode), 1);
	}
}

void	Client::delChannelAndRight(std::string channelName) {
	if (channelName.empty())
		return;
	std::map<std::string, std::string>::iterator it = this->_channelAndRight.find(channelName);
	if (it != this->_channelAndRight.end())
		this->_channelAndRight.erase(it);
}

bool	Client::checkRightFromChannelAndRight(std::string channelName, char mode) const {
	if (channelName.empty() || !mode)
		return false;
	std::map<std::string, std::string>::const_iterator it = this->_channelAndRight.find(channelName);
	
	if (it != this->_channelAndRight.end())
		if (it->second.find(mode) != it->second.npos)
			return true;
	return false;
}

const std::string	Client::getRightFromChannel(std::string channelName) const {
	std::map<std::string, std::string>::const_iterator it = this->_channelAndRight.find(channelName);
	if (it != this->_channelAndRight.end())
		return it->second;
	return "";
}

std::map<std::string, std::string>	Client::getChannelAndRight(void) {
	return this->_channelAndRight;
}

/*** Setters ***/

void	Client::setIsRegistered(bool value) {this->_isRegistered = value;}
void	Client::setUsername(std::string username) {this->_username = username;}
void	Client::setNickname(std::string nickname) {this->_nickname = nickname;}
void	Client::setRealname(std::string realname) {this->_realname = realname;}
void	Client::setHostname(std::string hostname) {this->_hostname = hostname;}
void	Client::setPassword(std::string password) {this->_password = password;}
void	Client::setUserModes(char mode) {
	if (this->_userModes.find(mode) == this->_userModes.npos)
		this->_userModes += mode;
}
void	Client::setServerOP(bool value) {this->_serverOP = value;}

/*** Getters ***/

bool						Client::getIsRegistered(void) const {return this->_isRegistered;}
const std::string			Client::getUsername(void) const {return this->_username;}
const std::string			Client::getNickname(void) const {return this->_nickname;}
const std::string			Client::getRealname(void) const {return this->_realname;}
const std::string			Client::getHostname(void) const {return this->_hostname;}
const std::string			Client::getPassword(void) const {return this->_password;}
const std::string			Client::getPrefix(void) const {return (":" + this->getNickname() + "!" + this->getUsername() + "@" + this->getHostname());}
const std::string			Client::getUserModes(void) const {return this->_userModes;}
bool						Client::getServerOP(void) const {return this->_serverOP;}
std::vector<std::string>	Client::getActiveChannels(void) const {return this->_activeChannels;}
std::vector<std::string>	Client::getAllChanWithRight(void) {
	std::vector<std::string>						channels;
	std::map<std::string, std::string>::iterator	it;
	it = this->_channelAndRight.begin();
	while (it != this->_channelAndRight.end()) {
		if (!it->first.empty())
			channels.push_back(it->first);
		++it;
	}
	return channels;
}
