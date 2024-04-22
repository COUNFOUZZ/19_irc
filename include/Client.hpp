#pragma once

#include <iostream>

class Client
{
	private:
		Client(void) {}

		int	_socket;
		std::string	_username;
		std::string	_nickname;

	public:
		Client(int socket);
		~Client(void);

	/*** Setters ***/
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);

	/*** Getters ***/
		const std::string	getUsername(void);
		const std::string	getNickname(void);
};
