#include "../include/Server.hpp"

void	Server::_quit(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(arg);
	static_cast<void>(cl);
	std::cout << "[" << socket << "]" << this->_mapSocketAndClients[socket].getNickname() << ": CLIENT QUIT THE SERVER" << std::endl;
	FD_CLR(socket, &this->_masterSet);
	this->_mapSocketAndClients.erase(socket);
	close(socket);
}