#include "../include/Server.hpp"

bool	g_shutdown = false;

static void	shutdown(int) {
	g_shutdown = true;
}

/*
int	main(int argc, char **argv) {
	if (argc != 3) {
		return std::cerr << "Invalid number of arguments (./ircserv <port> <password>)" << std::endl, 1;
	}

	signal(SIGINT, shutdown);
	signal(SIGQUIT, shutdown);
	signal(SIGTSTP, SIG_IGN);
	try {
		Server	server(argv[1], argv[2]);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
*/

int main()
{
	Client cli;
	Channel chan;

	shutdown(1);
	if (g_shutdown == false)
	{
		std::cout << "Test" << std::endl;
	}

	std::cout << "userModes : " << cli.getUserModes() << std::endl;
	std::cout << "channelModes : " << chan.getChannelModes() << std::endl;

	cli.setUserModes("itkii");
	chan.setChannelModes("tki");

	std::cout << "userModes : " << cli.getUserModes() << std::endl;
	std::cout << "channelModes : " << chan.getChannelModes() << std::endl;

	if (cli.getUserModes().find("i") == cli.getUserModes().npos)
	{
		std::cout << "No i" << std::endl;
	}
	else
		std::cout << "Yes i" << std::endl;

	cli.delUserModes('i');
	chan.delChannelModes('i');
	std::cout << "userModes : " << cli.getUserModes() << std::endl;
	std::cout << "channelModes : " << chan.getChannelModes() << std::endl;
}
