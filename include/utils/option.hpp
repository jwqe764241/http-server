#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "utils/utils.hpp"

#include "exceptions/parse_exception.hpp"


template <typename t_key, typename t_val>
class option
{
private:
	std::map<t_key, t_val> container;
	option();

public:
	//copy
	option(const option& option)
	{
		container = option.container;
	}

	//move
	option(option&& option)
	try
	{
		for(auto& pair : option)
		{
			container[pair.first] = std::move(pair.second);
			container.erase(pair.first);
		}
	}
	catch (std::out_of_range exception)
	{
		//exception if option have no key
		throw parse_exception("have no option in target option");
	}

	virtual ~option()
	{
		//nothing??
	}

	void add(const std::pair<t_key, t_val>& element)
	{
		container.insert(element);
	}

	int remove(const t_key key)
	{
		return container.erase(key);
	}

	t_key operator[](const t_key key)
	{
		return container[key];
	}
};