#pragma once

#include <iostream>

class part
{
private:
	std::string name;

public:
	part(std::string name);
	~part();

	std::string get_name() const;
};