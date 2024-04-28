#pragma once

#include "./config.hpp"

#define	ERR_UNKNOWNCOMMAND(command, reason) ("421 " + command + " :" + reason + "\r\n")
#define	ERR_NONICKNAMEGIVEN(nickname) (std::string(":") + SERVER_NAME + " 431 *" + nickname + " :No nickname given\r\n")
#define	ERR_ERRONEUSNICKNAME(reason) ("432 :Erroneus nickname\r\n")
#define	ERR_NICKNAMEINUSE(nick) ("433 " + nick + " :Nickname is already in use\r\n")
#define ERR_PASSWDMISMATCH(nickname) (std::string(":") + SERVER_NAME + " 464 " + nickname + " :Password incorrect\r\n")