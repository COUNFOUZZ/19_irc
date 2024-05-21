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
		std::string					_channelModes;
		std::string					_password;

		void	_addOperator(std::string nickname);
		void	_refreshAllUsersList(std::string users) const;
		void	_eraseUserFromChannel(Client& client);
	public:
		Channel(void);
		Channel(std::string channelName);
		~Channel(void);

		void	addUser(Client& client);
		void	clientAnnounceHimself(Client client) const;
		void	broadcast(std::string message, Client cl) const;
		bool	isUserIsInChannel(std::string nickname) const;
		void	delChannelModes(char mode);
		void	printOperator(void) const;
		void	rplNameAndEnd(Client client) const;
		bool	isInOpVector(std::string nickname) const;
		void	delUserFromChannel(std::string nickname);

	/*** Setters ***/
		void	setChannelName(std::string channelName);
		void	setTopic(std::string topic);
		void	setChannelModes(char mode);
		void	setPassword(std::string password);

	/*** Getters ***/
		const std::string	getChannelName(void) const;
		const std::string	getTopic(void) const;
		std::vector<Client>	getClients(void);
		const std::string	getChannelModes(void) const;
		size_t				getNbrOfClient(void) const;
		std::string			getPassword(void) const;
};
