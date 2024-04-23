#pragma once

#include <iostream>

class Client
{
	private:

		int			_socket;
		bool		_isRegistred;
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
		bool				getIsRegistred(void) const;
		const std::string	getUsername(void) const;
		const std::string	getNickname(void) const;
};
