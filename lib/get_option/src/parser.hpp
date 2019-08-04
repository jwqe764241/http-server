#pragma once

#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <initializer_list>
#include <iostream>

#include "option.hpp"

auto find_option(std::string name, std::vector<cmd::option>& options)
{
	auto it = std::find_if(options.begin(), options.end(), [&name](const cmd::option& o) {
		return o.get_name() == name || o.get_short_name() == name;
		});

	return it;
}

namespace cmd 
{
	class parser
	{
	private:
		//store parsed options
		std::vector<std::pair<option, std::vector<std::string>>> parsed_option;

	private:
		void parse(int argc, char** argv, std::vector<option> options)
		{
			for (int i = 1; i < argc; ++i)
			{
				std::string current_value = argv[i];

				auto it = find_option(current_value, options);
				if (it != options.end())
				{
					option option = *it;

					int range_end = i + 1 + option.get_argument_count();
					if (range_end > argc)
					{
						range_end = argc;
					}

					std::vector<std::string> arguments;

					for (int j = i + 1; j < range_end; ++j)
					{
						std::string argument = argv[j];

						auto it = find_option(argument, options);
						if (it == options.end())
						{
							arguments.push_back(argument);
						}
						else
						{
							break;
						}
					}

					add_option(option, arguments);

					i += arguments.size();
				}
			}
		}

		auto find(std::string name)
		{
			auto it = std::find_if(parsed_option.begin(), parsed_option.end(), [name](const std::pair<option, std::vector<std::string>>& e) {
				const option o = e.first;
				return o.get_name() == name || o.get_short_name() == name;
				});

			return it;
		}

		void add_option(option o, std::vector<std::string> values)
		{
			parsed_option.push_back(std::pair<option, std::vector<std::string>>(o, values));
		}

	public:
		parser(int argc, char** argv, std::initializer_list<option> options)
		{
			parse(argc, argv, options);
		}

		bool has_option(std::string name)
		{
			auto it = find(name);

			return it != parsed_option.end() ? true : false;
		}

		std::vector<std::string> get_arguments(std::string name)
		{
			auto it = find(name);

			if (it != parsed_option.end())
			{
				return it->second;
			}
			else
			{
				return {};
			}
		}

		int get_argument_size(std::string name)
		{
			auto it = find(name);

			if (it != parsed_option.end())
			{
				return it->second.size();
			}
			else
			{
				return {};
			}
		}
	};
}