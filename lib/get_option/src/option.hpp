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
		option(std::string name, int argument_count);
		option(std::string name, std::string short_name, int argument_count);
		option(std::string name);
		option(std::string name, std::string short_name);

		std::string get_name() const;
		std::string get_short_name() const;
		int get_argument_count() const;
	};
}