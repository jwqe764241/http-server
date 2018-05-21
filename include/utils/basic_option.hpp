#pragma once

#include <string>
#include <map>

#include "utils/utils.hpp"

#include "exceptions/parse_exception.hpp"


_IMPLEMENT_SCOPE
namespace option{

template <typename t_key, typename t_val>
class basic_option
{
protected:
	std::map<t_key, t_val> container;

public:
	basic_option(){}

	basic_option(const basic_option& option)
	{
		container = option.container;
	}

	basic_option(basic_option&& option)
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
		//exception if option has no key
		throw parse_exception("no option in target option");
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

	t_key operator[](const t_key key)
	{
		return container[key];
	}

	const std::map<t_key, t_val>& get_container()
	{
		return container;
	}
};

}
_IMPLEMENT_END