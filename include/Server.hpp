#pragma once

#include <iostream>
#include <cctype>
#include <sstream>

class Server {
	private:
		int			_port;
		std::string	_password;

		bool	_arrIsDigit(char* nbr);
	public:
		Server(void);
		Server(char* port, char* password);
		~Server(void);
};