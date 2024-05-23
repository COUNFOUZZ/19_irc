#pragma once

#include <iostream>
#include <sys/socket.h>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>

class Client
{
	private:
		int									_socket;
		bool								_isRegistered;
		std::string							_username;
		std::string							_nickname;
		std::string							_realname;
		std::string							_hostname;
		std::string							_password;
		std::string							_userModes;
		bool								_serverOP;
		std::vector<std::string>			_activeChannels;
		std::map<std::string, std::string>	_channelAndRight;

		std::vector<std::string>::iterator	_giveIteratorActiveChannel(std::string channelName);
	
	public:
		Client(void);
		Client(int socket);
		~Client(void);

		Client&	operator=(const Client& dest);

		void	sendMessage(const std::string& message) const;
		bool	isReadyToBeRegister(void) const;
		void	delUserModes(char mode);
		void	addActiveChannel(const std::string channelName);
		bool	isInChannel(const std::string chanelName) const;
		void	delActiveChannel(const std::string channelName);
		size_t	nbrOfActiveChannel(void) const;

	/*** Channel/right ***/
		void				addChannelAndRight(std::string channelName, char mode);
		void				delARightFromChannelAndRight(std::string channelName, char mode);
		void				delChannelAndRight(std::string channelName);
		bool				checkRightFromChannelAndRight(std::string channelName, char mode) const;
		const std::string	getRightFromChannel(std::string channelName) const;

	/*** Setters ***/
		void	setIsRegistered(bool value);
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);
		void	setRealname(std::string realname);
		void	setHostname(std::string hostname);
		void	setPassword(std::string password);
		void	setUserModes(char mode);
		void	setServerOP(bool value);

	/*** Getters ***/
		bool						getIsRegistered(void) const;
		const std::string			getUsername(void) const;
		const std::string			getNickname(void) const;
		const std::string			getRealname(void) const;
		const std::string			getHostname(void) const;
		const std::string			getPassword(void) const;
		const std::string			getPrefix(void)	const;
		const std::string			getUserModes(void) const;
		bool						getServerOP(void) const;
		std::vector<std::string>	getActiveChannels(void) const;
};
