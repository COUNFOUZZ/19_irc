#include "../include/Server.hpp"

Server::Server(void) : _port(0), _password("") {}
Server::Server(char* port, char* password) : _password(password) {
	if (!this->_arrIsDigit(port))
		throw std::runtime_error("port is not a digit !");
	std::stringstream	ss(port);

	ss >> this->_port;
	if (ss.fail())
		throw std::runtime_error("stringstream failed !");
	if (this->_port < 1 && this->_port > 65535)
		throw std::runtime_error("bad range of port !");
	if (this->_password.empty())
		throw std::runtime_error("Password can't be empty !");
}
Server::~Server(void) {}

bool	Server::_arrIsDigit(char* nbr) {
	if (!nbr[0])
		return false;
	for (int i = 0; nbr[i]; ++i) {
		if (!isdigit(nbr[i]))
			return false;
	}
	return true;
}