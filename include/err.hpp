#pragma once

#include "./config.hpp"

#define	ERR_UNKNOWNCOMMAND(command, reason) ("421 " + command + " :" + reason + "\r\n")