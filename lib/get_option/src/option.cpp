#include "option.hpp"

namespace cmd
{
	option::option(std::string name, int argument_count)
		: name(name), argument_count(argument_count)
	{
	}

	option::option(std::string name, std::string short_name, int argument_count)
		: name(name), short_name(short_name), argument_count(argument_count)
	{
	}

	option::option(std::string name)
		: option(name, 0)
	{
	}

	option::option(std::string name, std::string short_name)
		: option(name, short_name, 0)
	{
	}

	std::string option::get_name() const
	{
		return name;
	}

	std::string option::get_short_name() const
	{
		return short_name;
	}

	int option::get_argument_count() const
	{
		return argument_count;
	}
}