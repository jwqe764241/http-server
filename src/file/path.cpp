#include "file/path.hpp"

path::path()
{
}

path::path(std::string path_string)
{
	std::replace(path_string.begin(), path_string.end(), '\\', '/');

	int position = std::string::npos;
	position = path_string.find(character::PATH_DIVIDER, 0);

	if (position == 0)
	{
		//has divider at fist
		position += character::PATH_DIVIDER.size();
	}
	else if (position > 0)
	{
		//has divider, not fist
		append(part(path_string.substr(0, position)));
		position += character::PATH_DIVIDER.size();
	}
	else if (position == std::string::npos && path_string.size() > 0)
	{
		//has no divider, but has part text
		append(part(path_string));
		return;
	}
	else
	{
		//not supported
		throw std::invalid_argument("this path string not supported");
	}

	//get directories after first directory
	int prev_position = position;
	while ((position = path_string.find(character::PATH_DIVIDER, position)) != std::string::npos)
	{
		append(part(path_string.substr(prev_position, position - prev_position)));
		position += character::PATH_DIVIDER.size();

		prev_position = position;
	}

	//if path not ended with divider
	if (prev_position < path_string.size())
	{
		append(part(path_string.substr(prev_position, path_string.size())));
	}
}

path::~path()
{
}

void path::append(const std::string& path_string)
{
	//if path string has divider, it can be consist of many folder
	if (path_string.find(character::PATH_DIVIDER) != std::string::npos)
	{
		this->append(path(path_string));
	}
	else
	{
		this->append(part(path_string));
	}
}

void path::append(const path& path)
{
	this->parts.insert(parts.end(), path.parts.begin(), path.parts.end());
}

void path::append(const part& part)
{
	this->parts.push_back(part);
}

part path::get_part(int index)
{
	try
	{
		return parts.at(index);
	}
	catch (const std::exception & e)
	{
		throw;
	}
}

part path::get_first_part()
{
	return parts.front();
}

part path::get_last_part()
{
	return parts.back();
}

std::string path::get_path_string()
{
	//TODO: how to know this path starts with root directory?
	std::stringstream stream;

	for (const part& part : parts)
	{
		stream << part.get_name() << "\\";
	}

	return stream.str();
}

void path::operator+=(const std::string& lhs)
{
	append(lhs);
}

void path::operator+=(const path& lhs)
{
	append(lhs);
}