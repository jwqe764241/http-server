#pragma once

#include <iostream>
#include "event/event.hpp"


class basic_event : public event
{
public:
	void notify() override
	{
		std::cout << "event called" << std::endl;
	}
};