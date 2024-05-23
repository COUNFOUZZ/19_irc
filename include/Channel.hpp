#pragma once

#include "../include/Client.hpp"
#include "../include/rpl.hpp"

class Channel
{
	private:
		std::string					_channelName;
		std::string					_topic;
		std::vector<Client>			_clients;
		std::vector<std::string>	_operators;
		std::vector<std::string>	_inviteList;
		std::string					_channelModes;
		std::string					_password;
		int							_limit;
		bool						_inviteOnly;

		void	_refreshAllUsersList(std::string users) const;
		void	_eraseUserFromChannel(Client& client);
	public:
		Channel(void);
		Channel(std::string channelName);
		~Channel(void);

		void	addUser(Client& client);
		void	addOperator(std::string nickname);
		void	delOperator(std::string nickname);
		void	clientAnnounceHimself(Client client) const;
		void	broadcast(std::string message, Client cl) const;
		bool	isUserIsInChannel(std::string nickname) const;
		void	delChannelModes(char mode);
		void	printOperator(void) const;
		void	rplNameAndEnd(Client client) const;
		bool	isInOpVector(std::string nickname) const;
		void	delUserFromChannel(std::string nickname);
		bool	checkAMode(char mode) const;
		void	addNicknameInInviteList(std::string nickname);
		void	delNicknameInInviteList(std::string nickname);
		void	clearInviteList(void);
		bool	checkIsInvited(std::string nickname) const;

	/*** Setters ***/
		void	setChannelName(std::string channelName);
		void	setTopic(std::string topic);
		void	setChannelModes(char mode);
		void	setPassword(std::string password);
		void	setLimit(int limit);
		void	setInviteOnly(bool value);

	/*** Getters ***/
		const std::string	getChannelName(void) const;
		const std::string	getTopic(void) const;
		std::vector<Client>	getClients(void);
		const std::string	getChannelModes(void) const;
		size_t				getNbrOfClient(void) const;
		std::string			getPassword(void) const;
		int					getLimit(void) const;
		size_t				getNbrInvited(void) const;
};
