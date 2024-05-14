#include "../include/Server.hpp"

Server::Server(char* port, char* password) : _password(password) {
	this->_portAndPasswordHandling(port);
	this->_initCmds();
	this->_initServer();
	this->_runServer();
}

Server::~Server(void) {}

bool	Server::_arrIsDigit(char* nbr) {
	if (!nbr[0])
		return false;
	for (int i = 0; nbr[i]; ++i) {
		if (!isdigit(nbr[i]))
			return false;
	}
	return true;
}

void	Server::_portAndPasswordHandling(char* port) {
	if (!this->_arrIsDigit(port))
		throw std::runtime_error("port is not a digit !");
	std::stringstream	ss(port);

	ss >> this->_port;
	if (ss.fail())
		throw std::runtime_error("stringstream failed !");
	if (this->_port < 1024 || this->_port > 49151)
		throw std::runtime_error("bad range of port ! (port available 1024 to 49151)");
	if (this->_password.empty())
		throw std::runtime_error("Password can't be empty !");
}

void	Server::_initCmds(void) {
	this->_commands["CAP"] = &Server::_cap;
	this->_commands["NICK"] = &Server::_nick;
	this->_commands["USER"] = &Server::_user;
	this->_commands["PASS"] = &Server::_pass;
	this->_commands["QUIT"] = &Server::_quit;
	this->_commands["PING"] = &Server::_ping;
	this->_commands["PRIVMSG"] = &Server::_privmsg;
	this->_commands["JOIN"] = &Server::_join;
	this->_commands["PART"] = &Server::_part;
}

void	Server::_initServer(void) {
	// Create a socket
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1)
		throw std::runtime_error("Can't create a socket !");

	int opt = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		close(this->_serverSocket);
		throw std::runtime_error("setsockopt failed");
	}
		
	// Bind the socket to an IP / port
	memset(&this->_serverAddress, 0, sizeof(this->_serverAddress));
	this->_serverAddress.sin_family = AF_INET;
	this->_serverAddress.sin_port = htons(this->_port);   // host to network short
	this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
	if (inet_pton(AF_INET, "0.0.0.0", &this->_serverAddress.sin_addr) != 1) {
		close(this->_serverSocket);
		throw std::runtime_error("inet_pton");
	}

	if (bind(this->_serverSocket, (struct sockaddr *)&this->_serverAddress, sizeof(this->_serverAddress)) == -1) {
		close(this->_serverSocket);
		throw std::runtime_error("Can't bind !");
	}

	if (listen(this->_serverSocket, SOMAXCONN) == -1) {
		close(this->_serverSocket);
		throw std::runtime_error("Can't listen !");
	}

	// Initialize the master set to 0
	FD_ZERO(&this->_masterSet); 
	FD_SET(this->_serverSocket, &this->_masterSet);
}

int Server::_acceptClient(void) {
	sockaddr_storage	client_addr;
	socklen_t 			addr_len = sizeof(client_addr);

	int clientSocket = accept(this->_serverSocket, (struct sockaddr *)&client_addr, &addr_len);
	if (clientSocket < 0)
		std::cerr << "Can't accept client!" << std::endl;
	FD_SET(clientSocket, &this->_masterSet);
	this->_mapSocketAndClients.insert(std::pair<int, Client>(clientSocket, Client(clientSocket)));
	this->_mapNicknameAndClients.insert(std::pair<std::string, Client>(this->_mapSocketAndClients[clientSocket].getNickname(), this->_mapSocketAndClients[clientSocket]));
	return (clientSocket);
}

std::vector<std::string>	Server::_getCommand(std::string input) {
	std::vector<std::string>	cmds;

	if (input.empty())
		return cmds;
	if (!input.empty() && input[input.size() - 1] == '\r')
		input.erase(input.size() - 1);
	std::string			buffer;
	std::istringstream	ss(input);
	while (std::getline(ss, buffer, ' '))
		cmds.push_back(buffer);
	return cmds;
}

void	Server::_commandHandling(int socket, std::vector<std::string> commandsAndArgs) {
	if (commandsAndArgs.empty())
		return;
	std::string command(commandsAndArgs[0]);
	commandsAndArgs.erase(commandsAndArgs.begin());
	if (this->_commands.find(command) != this->_commands.end())
		(this->*_commands[command])(socket, commandsAndArgs, this->_mapSocketAndClients[socket]);
	else {
		std::string	errorMsg(ERR_UNKNOWNCOMMAND(command, "command not found !"));
		if (send(socket, errorMsg.c_str(), errorMsg.size(), 0) == -1)
			throw std::runtime_error("send() !");
	}
}

void	Server::_welcome(int socket) {
	if (!this->_mapSocketAndClients[socket].getIsRegistered() && !this->_mapSocketAndClients[socket].getPassword().empty() && this->_mapSocketAndClients[socket].isReadyToBeRegister()) {
		this->_mapSocketAndClients[socket].setIsRegistered(true);
		this->_mapSocketAndClients[socket].sendMessage(RPL_WELCOME(this->_mapSocketAndClients[socket].getNickname()));
	}
}

void	Server::_clientHandling(int socket) {
	char	buffer[2048] = {0};
	int		bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0);

	if (bytesReceived <= 0) {
		FD_CLR(socket, &this->_masterSet);
		this->_mapSocketAndClients.erase(socket);
		close(socket);
	} else {
		buffer[bytesReceived] = '\0';
		std::istringstream	ss(buffer);
		std::string			line;

		while (std::getline(ss, line, '\n')) {
			std::vector<std::string>	commands = this->_getCommand(line);
			std::cout << "======= Socket " << socket << " =======" << std::endl;
			for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl << "========================" << std::endl;
			std::cout << std::endl;
			this->_commandHandling(socket, commands);
		}
	}
}

//	tuto select() and FD_SET,...
//	https://www.youtube.com/watch?v=Y6pFtgRdUts
void	Server::_runServer(void) {
	int fdMax = this->_serverSocket;
	while (!g_shutdown) {
		fd_set	readySockets = this->_masterSet;
		if (select(fdMax + 1, &readySockets, NULL, NULL, NULL) < 0)
			break;
		for (int i = 0; i <= fdMax; i++){
			if (FD_ISSET(i, &readySockets)) {
				if (i == this->_serverSocket) {
					int clientSocket = this->_acceptClient();
					if (fdMax < clientSocket)
						fdMax = clientSocket;
				} else {
					this->_clientHandling(i);
				}
			}
		}
	}
}
