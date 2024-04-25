#pragma once

#include "./config.hpp"

#define	ERR_UNKNOWNCOMMAND(command, reason) ("421 " + command + " :" + reason + "\r\n")

#define	ERR_ERRONEUSNICKNAME(reason) ("432 :Erroneus nickname\r\n")

#define	ERR_NICKNAMEINUSE(nick) ("433 " + nick + " :Nickname is already in use\r\n")
