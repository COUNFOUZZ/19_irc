#pragma once

#include <iostream>
#include <cctype>
#include <sstream>
#include <sys/socket.h>	// socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h>	// sockaddr_in and inet_ntoa()
#include <arpa/inet.h>	// htons(), htonl(), ntohs(), ntohl(), inet_addr()
#include <sys/epoll.h>	// epoll_create(), epoll_ctl(), epoll_wait()
#include <unistd.h>		// close()
#include <fcntl.h>		// fcntl()
#include <cstring>		// memset()

class Server {
	private:
		Server(void) {}

		int					_port;
		std::string			_password;
		int					_serverSocket;
		struct sockaddr_in	_serverAddress;
		fd_set				_masterSet;

		void	_portAndPasswordHandling(char* port);
		bool	_arrIsDigit(char* nbr);
		void	_initServer(void);
	public:
		Server(char* port, char* password);
		~Server(void);
};