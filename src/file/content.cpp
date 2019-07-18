#include "file/content.hpp"

content::content(std::string location)
try
{
	elements = path(location);
}
catch (...)
{
	throw;
}

std::string content::get_path()
{
	return elements.get_real_path_string();
}

std::string content::get_extension()
{
	std::string last_element = elements.get_last_part().get_name();

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
	return std::ifstream(elements.get_real_path_string(), std::ifstream::binary);
}

std::string content::get_type()
{
	return type_map[get_extension()];
}

void content::append(const content& content)
{
	this->elements.append(content.elements);
}