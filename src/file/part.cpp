#include "file/part.hpp"

part::part(std::string name)
{
	for (std::string::iterator i = name.begin(); i != name.end(); ++i)
	{
		if ((*i) == ' ')
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

part::~part()
{
}

std::string part::get_name() const
{
	return name;
}