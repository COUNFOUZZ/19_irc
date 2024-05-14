#pragma once

#include "./config.hpp"

#define RPL_WELCOME(nickname) (std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the Internet Relay Network\r\n")
#define RPL_NOTOPIC(channel) (std::string(":") + SERVER_NAME + " 331 " + "No topic set for channel " + channel + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (std::string(":") + SERVER_NAME + " 332 " + nickname + " " + channel + " :" + topic + "\r\n")