#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "utils/utils.hpp"
#include "utils/basic_option.hpp"

#include "exceptions/parse_exception.hpp"

_IMPLEMENT_SCOPE
namespace option{

class file_option : public basic_option<std::string, std::string>
{
public:
	file_option();
	file_option(std::ifstream& file_stream);
	file_option(std::ifstream&& file_stream);

	void parse(std::ifstream& file_stream);
};

}
_IMPLEMENT_END