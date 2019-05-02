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

std::string content::get_path()
{
	return location;
}

std::string content::get_extension()
{
	std::string last_element = elements.get_last();

	size_t pos = last_element.find_last_of('.');
	if (pos != std::string::npos)
	{
		return last_element.substr(pos + 1);
	}
	else
	{
		return "";
	}
}

std::ifstream content::get_stream()
{
	return std::ifstream(location, std::ifstream::binary);
}

std::string content::get_type()
{
	std::string extension = get_extension();
	return type_map[extension];
}