#pragma once

#include "./config.hpp"

#define RPL_WELCOME(nickname) (std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the Internet Relay Network\r\n")
#define RPL_NOTOPIC(channel) (std::string(":") + SERVER_NAME + " 331 " + "No topic set for channel " + channel + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (std::string(":") + SERVER_NAME + " 332 " + nickname + " " + channel + " :" + topic + "\r\n")
#define RPL_NAMREPLY(nickname, channel, usersList) (std::string(":") + SERVER_NAME + " 353 " + nickname + " = " + channel + " :" + usersList  + "\r\n")
#define RPL_ENDOFNAMES(channel, nickname) (std::string(":") + SERVER_NAME + " 366 " + nickname + " " + channel + " :End of NAMES list\r\n")
#define RPL_MOTDSTART(motd) (std::string(":") + SERVER_NAME + " 375 " + motd + "\r\n")
