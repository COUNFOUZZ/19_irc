#pragma once

#include <iostream>

class Client
{
	private:

		int	_socket;
		std::string	_username;
		std::string	_nickname;

	public:
		Client(void);
		Client(int socket);
		~Client(void);

		Client&	operator=(const Client& dest);

	/*** Setters ***/
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);

	/*** Getters ***/
		const std::string	getUsername(void);
		const std::string	getNickname(void);
};
