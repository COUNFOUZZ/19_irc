#include "../include/Server.hpp"

void	Server::_quit(int socket, std::vector<std::string>& arg) {
	std::cout << "[" << socket << "]" << this->_mapSocketAndClients[socket].getNickname() << ": CLIENT QUIT THE SERVER" << std::endl;
	if (this->_mapSocketAndClients[socket].nbrOfActiveChannel()) {
		std::vector<std::string>	activeChannels = this->_mapSocketAndClients[socket].getActiveChannels();

		for (size_t i = 0; i < activeChannels.size(); ++i) {
			std::vector<std::string>	toDelete;
			toDelete.push_back(activeChannels[i]);
			for (size_t j = 0; j < arg.size(); ++j)
				toDelete.push_back(arg[j]);
			this->_part(socket, toDelete);
			toDelete.clear();
		}
	}
	FD_CLR(socket, &this->_masterSet);
	this->_mapSocketAndClients.erase(socket);
	close(socket);
}