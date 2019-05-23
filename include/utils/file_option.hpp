#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "utils/basic_option.hpp"

class file_option : public basic_option<std::string, std::string>
{
public:
	file_option();
	file_option(std::ifstream& file_stream);
	file_option(std::ifstream&& file_stream);
	~file_option();

	void parse(std::ifstream& file_stream);

	file_option& operator=(const file_option& other);
};