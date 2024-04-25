#pragma once

#include <iostream>
#include <sys/socket.h>

class Client
{
	private:

		int			_socket;
		bool		_isRegistered;
		std::string	_username;
		std::string	_nickname;

	public:
		Client(void);
		Client(int socket);
		~Client(void);

		Client&	operator=(const Client& dest);


		void	sendMessage(const std::string& message) const;

	/*** Setters ***/
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);

	/*** Getters ***/
		bool				getIsRegistered(void) const;
		const std::string	getUsername(void) const;
		const std::string	getNickname(void) const;
};
