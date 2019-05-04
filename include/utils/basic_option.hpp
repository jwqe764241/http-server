#pragma once

#include <iostream>
#include <string>
#include <map>

#include "exceptions/parse_exception.hpp"

template <typename t_key, typename t_val>
class basic_option
{
protected:
	std::map<t_key, t_val> container;

public:
	basic_option(){}

	basic_option(basic_option& option)
	{
		container = option.container;
	}
	
	basic_option(basic_option<t_key, t_val>&& option)
	{
		for (auto& pair : option.get_container())
		{
			container[pair.first] = std::move(pair.second);
			container.erase(pair.first);
		}
	}
		
	virtual ~basic_option()
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

	t_val operator[](const t_key key)
	{
		return container[key];
	}

	const std::map<t_key, t_val>& get_container()
	{
		return container;
	}
};