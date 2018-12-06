#pragma once

#include <iostream>

class event
{
public:
	virtual void notify() = 0;
};