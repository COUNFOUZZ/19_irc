#pragma once

#include <iostream>
#include <sys/socket.h>
#include <algorithm>

class Client
{
	private:

		int			_socket;
		bool		_isRegistered;
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		std::string	_hostname;
		std::string	_password;
		std::string	_userModes;

	public:
		Client(void);
		Client(int socket);
		~Client(void);

		Client&	operator=(const Client& dest);


		void	sendMessage(const std::string& message) const;
		bool	isReadyToBeRegister(void) const;

	/*** Setters ***/
		void	setIsRegistered(bool value);
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);
		void	setRealname(std::string realname);
		void	setHostname(std::string hostname);
		void	setPassword(std::string password);
		void	setUserModes(char mode);
		void	delUserModes(char mode);

	/*** Getters ***/
		bool			getIsRegistered(void) const;
		const std::string	getUsername(void) const;
		const std::string	getNickname(void) const;
		const std::string	getRealname(void) const;
		const std::string	getHostname(void) const;
		const std::string	getPassword(void) const;
		const std::string	getPrefix(void)	const;
		const std::string	getUserModes(void) const;
};
