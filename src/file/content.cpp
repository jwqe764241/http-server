#include "file/content.hpp"

content::content(std::string location)
try : location(location)
{
	elements = path(location);
}
catch (...)
{
	throw;
}

std::string content::get_extension()
{
	std::string last_element = elements.get_last();

	size_t pos = last_element.find_last_of('.');
	if (pos != std::string::npos)
	{
		return last_element.substr(pos);
	}
	else
	{
		return "";
	}
}

std::string content::get_type()
{
	return type_map[get_extension()];
}