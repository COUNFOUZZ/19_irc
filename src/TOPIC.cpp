#include "../include/Server.hpp"

void	Server::_topic(int socket, std::vector<std::string>& arg, Client cl) {
	static_cast<void>(cl);
	
	std::string	username;
	std::string	topic;
	std::string	channelName = arg[0];
	if (arg.size() == 1) {
		topic = this->_channels[channelName].getTopic();
		if (topic.empty()) {
			// print : No topic set for channel #channel
			this->_mapSocketAndClients[socket].sendMessage(RPL_NOTOPIC(channelName)); // change where the message is displayed. Should be in channel, not in server
		}
		else {
			// print : Topic for #channel is "messageOfTopic"
			this->_mapSocketAndClients[socket].sendMessage(RPL_TOPIC(username, channelName, topic)); // change where message is displayed
		}
	}
	else {
		// check modes du channel
		// si mode topic on 
		// check rights
		size_t	i = 1;
		while (i < arg.size()) {
			topic += arg[i];
			if (i != arg.size() - 1)
				topic += " ";
			i++;
		}
		this->_channels[channelName].setTopic(topic);
		//print : nickname has changed topic for #channel to "messageOfTopic"
		// print : Topic set by nickname on 'date and time'
	}
}
