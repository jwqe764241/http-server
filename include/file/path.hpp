#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "part.hpp"
#include "utils/utils.hpp"

class path
{
private:
	std::vector<part> parts;

public:
	path()
	{
	}

	path(std::string path_string)
	{
		std::replace(path_string.begin(), path_string.end(), '\\', '/');

		int position = std::string::npos;
		position = path_string.find(character::PATH_DIVIDER, 0);

		if(position == 0)
		{
			//has divider at fist
			position += character::PATH_DIVIDER.size();
		}
		else if(position > 0)
		{
			//has divider, not fist
			append(part(path_string.substr(0, position)));
			position += character::PATH_DIVIDER.size();
		}
		else if(position == std::string::npos && path_string.size() > 0)
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
		while((position = path_string.find(character::PATH_DIVIDER, position)) != std::string::npos)
		{
			append(part(path_string.substr(prev_position, position - prev_position)));
			position += character::PATH_DIVIDER.size();

			prev_position = position;
		}

		//if path not ended with divider
		if(prev_position < path_string.size())
		{
			append(part(path_string.substr(prev_position, path_string.size())));
		}
	}

	~path()
	{
	}
	
	void append(const std::string& path_string)
	{
		//if path string has divider, it can be consist of many folder
		if(path_string.find(character::PATH_DIVIDER) != std::string::npos)
		{
			this->append(path(path_string));
		}
		else
		{
			this->append(part(path_string));
		}
	}

	void append(const path& path)
	{
		this->parts.insert(parts.end(), path.parts.begin(), path.parts.end());
	}

	void append(const part& part)
	{
		this->parts.push_back(part);
	}

	std::string get(int index)
	{
		try
		{
			return parts.at(index).get_name();
		}
		catch (const std::exception & e)
		{
			throw;
		}
	}

	std::string get_first()
	{
		return parts.front().get_name();
	}

	std::string get_last()
	{
		return parts.back().get_name();
	}

	std::string get_path()
	{
		//TODO: how to know this path starts with root directory?
		std::stringstream stream;

		for (const part& part : parts)
		{
			stream << part.get_name() << "\\";
		}

		return stream.str();
	}

	void operator+=(const std::string& lhs)
	{
		append(lhs);
	}
	void operator+=(const path& lhs)
	{
		append(lhs);
	}
};