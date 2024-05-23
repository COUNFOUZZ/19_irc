#pragma once

#include "./config.hpp"

#define RPL_WELCOME(nickname) (std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the Internet Relay Network\r\n")
#define RPL_NOTOPIC(nickname, channel) (std::string("331 ") + nickname + " " + channel + " No topic set for channel " + channel + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (std::string(":") + SERVER_NAME + " 332 " + nickname + " " + channel + " :" + topic + "\r\n")
#define RPL_NAMREPLY(nickname, channel, usersList) (std::string(":") + SERVER_NAME + " 353 " + nickname + " = " + channel + " :" + usersList  + "\r\n")
#define RPL_ENDOFNAMES(channel, nickname) (std::string(":") + SERVER_NAME + " 366 " + nickname + " " + channel + " :End of NAMES list\r\n")
#define RPL_MOTD(motd) (std::string(":") + SERVER_NAME + " 372 " + motd + "\r\n")
#define RPL_MOTDSTART(motd) (std::string(":") + SERVER_NAME + " 375 " + motd + "\r\n")
#define RPL_YOUREOPER(info) (std::string(":") + SERVER_NAME + " 381 You are now operator in " + info + ".\r\n")
#define RPL_INVITING(nickname, target, channel) (std::string(":") + SERVER_NAME + " 341 " + nickname + " " + target + " " + channel + "\r\n")
