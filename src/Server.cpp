#include "../include/Server.hpp"

Server::Server(char* port, char* password) : _password(password) {
	this->_portAndPasswordHandling(port);
	this->_initServer();
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

void	Server::_portAndPasswordHandling(char* port) {
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

void	Server::_initServer(void) {
	// Create a socket
    this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1)
        throw std::runtime_error("Can't create a socket !");

	int opt = 1;
    if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		close(this->_serverSocket);
	    throw std::runtime_error("setsockopt failed");
	}
    
    // Bind the socket to an IP / port
	memset(&this->_serverAddress, 0, sizeof(this->_serverAddress));
    this->_serverAddress.sin_family = AF_INET;
    this->_serverAddress.sin_port = htons(_port);   // host to network short
    this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
	if (inet_pton(AF_INET, "0.0.0.0", &this->_serverAddress.sin_addr) != 1) {
		close(this->_serverSocket);
		throw std::runtime_error("inet_pton");
	}

    if (bind(this->_serverSocket, (struct sockaddr *)&this->_serverAddress, sizeof(this->_serverAddress)) == -1) {
		close(this->_serverSocket);
		throw std::runtime_error("Can't bind !");
	}

    if (listen(this->_serverSocket, SOMAXCONN) == -1) {
		close(this->_serverSocket);
        throw std::runtime_error("Can't listen !");
	}

    // Initilize the master set to 0
    FD_ZERO(&this->_masterSet); 
    FD_SET(this->_serverSocket, &this->_masterSet);
}