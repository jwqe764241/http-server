#pragma once

#include <iostream>

class part
{
private:
	std::string name;

public:
	part(std::string name)
	{
		for(std::string::iterator i = name.begin(); i != name.end(); ++i)
		{
			if((*i) == ' ')
			{
				name.erase(i);
				++i;
			}
			else
			{
				break;
			}
		}

		this->name = name;
	}

	~part()
	{
	}

	std::string get_name()
	{
		return name;
	}
};