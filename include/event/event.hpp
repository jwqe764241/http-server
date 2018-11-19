#pragma once

#include <iostream>

class event
{
public:
	virtual void notify()
	{
		std::cout << "event called" << std::endl;
	}
};