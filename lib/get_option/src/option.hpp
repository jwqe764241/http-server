#pragma once

#include <string>
 
namespace cmd
{
	class option
	{
	private:
		std::string name;
		std::string short_name;
		int argument_count;

	public:
		option(std::string name, int argument_count)
			: name(name), argument_count(argument_count)
		{
		}
		option(std::string name, std::string short_name, int argument_count)
			: name(name), short_name(short_name), argument_count(argument_count)
		{
		}
		option(std::string name)
			: option(name, 0)
		{
		}
		option(std::string name, std::string short_name)
			: option(name, short_name, 0)
		{
		}

		std::string get_name() const
		{
			return name;
		}

		std::string get_short_name() const
		{
			return short_name;
		}

		int get_argument_count() const
		{
			return argument_count;
		}
	};
}