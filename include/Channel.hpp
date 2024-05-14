#pragma once

#include "../include/Client.hpp"
#include "../include/rpl.hpp"
#include <vector>

class Channel
{
	private:
		std::string			_channelName;
		std::string			_topic;
		std::vector<Client>	_client;

	public:
		Channel(void);
		Channel(std::string channelName);
		~Channel(void);

		void	addUser(Client client);
		void	clientAnnounceHimself(Client client) const;

		void	setChannelName(std::string channelName);
		void	setTopic(std::string topic);

		const std::string	getChannelName(void) const;
		const std::string	getTopic(void) const;
		void				getListOfUsers(Client client) const;
};

