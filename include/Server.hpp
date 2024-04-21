#pragma once

#include <iostream>
#include <cctype>
#include <sstream>
#include <csignal>		// signal()
#include <sys/socket.h>	// socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h>	// sockaddr_in and inet_ntoa()
#include <arpa/inet.h>	// htons(), htonl(), ntohs(), ntohl(), inet_addr()
#include <sys/epoll.h>	// epoll_create(), epoll_ctl(), epoll_wait()
#include <unistd.h>		// close()
#include <fcntl.h>		// fcntl()
#include <cstring>		// memset()
#include <map>

extern bool g_shutdown;

class Server {
	private:
		Server(void) {}

		int					_port;
		std::string			_password;
		int					_serverSocket;
		struct sockaddr_in	_serverAddress;
		fd_set				_masterSet;
		// map client here

		void	_portAndPasswordHandling(char* port);
		bool	_arrIsDigit(char* nbr);
		void	_initServer(void);
		void	_runServer(void);
		int		_acceptClient(void);
	public:
		Server(char* port, char* password);
		~Server(void);
};