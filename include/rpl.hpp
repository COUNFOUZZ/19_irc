#pragma once

#include "./config.hpp"

#define RPL_WELCOME(nickname)	(std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the Internet Relay Network\r\n")