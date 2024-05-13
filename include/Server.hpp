#pragma once

#include "../include/err.hpp"
#include "../include/rpl.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include <iostream>
#include <cctype>
#include <sstream>
#include <csignal>		// signal()
#include <sys/socket.h>	// socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h>	// sockaddr_in and inet_ntoa()
#include <arpa/inet.h>	// htons(), htonl(), ntohs(), ntohl(), inet_addr()
#include <unistd.h>		// close()
#include <fcntl.h>		// fcntl()
#include <cstring>		// memset()
#include <map>
#include <vector>
#include <iterator>

extern bool g_shutdown;

class Server {
	private:
		Server(void) {}
		typedef void (Server::*cmdFct)(int, std::vector<std::string>&, Client);

		int								_port;
		std::string						_password;
		int								_serverSocket;
		struct sockaddr_in				_serverAddress;
		fd_set							_masterSet;
		std::map<std::string, cmdFct> 	_commands;
		std::map<int, Client>			_mapSocketAndClients;
		std::map<std::string, Client>	_mapNicknameAndClients;
		std::map<std::string, Channel>	_channels;

		void						_portAndPasswordHandling(char* port);
		bool						_arrIsDigit(char* nbr);
		void						_initCmds(void);
		void						_initServer(void);
		void						_runServer(void);
		int							_acceptClient(void);
		void						_clientHandling(int socket);
		std::vector<std::string>	_getCommand(std::string input);
		void						_commandHandling(int socket, std::vector<std::string> commandsAndArgs);
		bool						_nickAlreadyTaken(std::string newNick, Client cl);
		bool						_isValidNickname(std::string nickname, Client cl);
		bool						_checkNickname(std::string nickname, Client cl);
		void						_welcome(int socket);
		bool						_isSpecialChar(std::string nickname) const;

		void	_cap(int socket, std::vector<std::string>& arg, Client cl);
		void	_nick(int socket, std::vector<std::string>& arg, Client cl);
		void	_user(int socket, std::vector<std::string>& arg, Client cl);
		void	_pass(int socket, std::vector<std::string>& arg, Client cl);
		void	_quit(int socket, std::vector<std::string>& arg, Client cl);
		void	_ping(int socket, std::vector<std::string>& arg, Client cl);
		void	_privmsg(int socket, std::vector<std::string>& arg, Client cl);
		void	_join(int socket, std::vector<std::string>& arg, Client cl);
	public:
		Server(char* port, char* password);
		~Server(void);
};
