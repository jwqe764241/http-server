#pragma once

#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <initializer_list>
#include <iostream>

#include "option.hpp"

namespace cmd 
{
	class parser
	{
	private:
		//store parsed options
		std::vector<std::pair<option, std::vector<std::string>>> parsed_option;

	private:
		void parse(int argc, char** argv, std::vector<option> options);
		auto find(std::string name);
		void add_option(option option, std::vector<std::string> values);

	public:
		parser(int argc, char** argv, std::initializer_list<option> options);

		bool has_option(std::string name);
		std::vector<std::string> get_arguments(std::string name);
	};
}