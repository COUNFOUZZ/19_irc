#pragma once

#include "../include/Client.hpp"
#include "../include/rpl.hpp"
#include <vector>
#include <iterator>
#include <algorithm>

class Channel
{
	private:
		std::string					_channelName;
		std::string					_topic;
		std::vector<Client>			_clients;
		std::vector<std::string>	_operators;
		std::string					_channelModes;

		bool	_isInOpVector(std::string nickname) const;
	public:
		Channel(void);
		Channel(std::string channelName);
		~Channel(void);

		void	addUser(Client client);
		void	clientAnnounceHimself(Client client) const;
		void	broadcast(std::string message, Client cl) const;
		void	eraseUserFromChannel(std::string nickname);
		bool	isUserIsInChannel(std::string nickname) const;
		void	delChannelModes(char mode);
		void	addOperator(std::string nickname);
		void	printOperator(void) const;
		void	rplNameAndEnd(Client client) const;

	/*** Setters ***/
		void	setChannelName(std::string channelName);
		void	setTopic(std::string topic);
		void	setChannelModes(char mode);

	/*** Getters ***/
		const std::string	getChannelName(void) const;
		const std::string	getTopic(void) const;
		std::vector<Client>	getClients(void) const;
		const std::string	getChannelModes(void) const;
		size_t				getNbrOfClient(void) const;
};
