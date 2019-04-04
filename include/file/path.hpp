#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "part.hpp"

static std::string divider = "/";

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
		position = path_string.find(divider, 0);

		if(position == 0)
		{
			//has divider at fist
			position += divider.size();
		}
		else if(position > 0)
		{
			//has divider, not fist
			parts.push_back(part(path_string.substr(0, position)));
			position += divider.size();
		}
		else if(position == std::string::npos && path_string.size() > 0)
		{
			//has no divider, but has part text
			parts.push_back(part(path_string));
			return;
		}
		else
		{
			//not supported
			throw std::invalid_argument("this path string not supported");
		}

		//get directories after first directory
		int prev_position = position;
		while((position = path_string.find(divider, position)) != std::string::npos)
		{
			parts.push_back(part(path_string.substr(prev_position, position - prev_position)));
			position += divider.size();

			prev_position = position;
		}

		//if path not ended with divider
		if(prev_position < path_string.size())
		{
			parts.push_back(part(path_string.substr(prev_position, path_string.size())));
		}
	}

	~path()
	{
	}
	
	void append(const std::string& path_string)
	{
		//if path string has divider, it can be consist of many folder
		if(path_string.find(divider) != std::string::npos)
		{
			*this += path(path_string);
		}
		else
		{
			this->parts.push_back(part(path_string));
		}
	}

	void append(const path& path)
	{
		this->parts.insert(parts.end(), path.parts.begin(), path.parts.end());
	}

	std::string get_path()
	{
	}


	//append parts
	void operator+=(const std::string& lhs)
	{
		append(lhs);
	}
	void operator+=(const path& lhs)
	{
		append(lhs);
	}
};