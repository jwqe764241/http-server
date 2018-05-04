#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "utils/utils.hpp"

#include "exceptions/parse_exception.hpp"

class option
{
private:
	std::map<std::string, std::string> container;

public:
	option();
	option(const option& option);
	option(const std::ofstream& file_stream);
	option(const std::string& option_string);
	virtual ~option();

	void parse(const std::ofstream& file_stream);
	void parse(const std::string& option_string);

	void add(const std::pair<std::string, std::string>& element);
	int remove(const std::string& key);

	std::string operator[](const std::string& key);
};