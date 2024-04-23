#include "../include/Server.hpp"

void	Server::_nick(int socket, std::vector<std::string>& arg, Client cl) {
	if (!cl.getIsRegistred()) {
		std::stringstream	ss;
		std::string			socketNbr;
		ss << socket;
		if (ss.fail())
			throw std::runtime_error("stringstream failed !");
		ss >> socketNbr;
		cl.setNickname(arg[0] + socketNbr);
	}
}