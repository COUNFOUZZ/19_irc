#pragma once

#include "../include/Client.hpp"
#include "../include/rpl.hpp"
#include <vector>
#include <iterator>

class Channel
{
	private:
		std::string			_channelName;
		std::string			_topic;
		std::vector<Client>	_clients;

	public:
		Channel(void);
		Channel(std::string channelName);
		~Channel(void);

		void	addUser(Client client);
		void	clientAnnounceHimself(Client client) const;
		void	broadcast(std::string message, Client cl) const;
		void	eraseUserFromChannel(std::string nickname);
		bool	isUserIsInChannel(std::string nickname) const;

		void	setChannelName(std::string channelName);
		void	setTopic(std::string topic);

		const std::string	getChannelName(void) const;
		const std::string	getTopic(void) const;
		std::vector<Client>	getClients(void) const;
		void				getListOfUsers(Client client) const;
};
