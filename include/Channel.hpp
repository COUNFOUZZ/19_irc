#pragma once

#include <iostream>

class Channel
{
	private:
		std::string	_name;

	public:
		Channel(void);
		Channel(std::string name);
		~Channel(void);

		const std::string	getName() const;
};

