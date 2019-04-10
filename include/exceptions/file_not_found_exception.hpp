#pragma once

#include <string>
#include <exception>

#include "utils/utils.hpp"

_IMPLEMENT_SCOPE

class file_not_found_exception : public std::exception
{
private:
	std::string msg;
	std::string file_name;

public:
	file_not_found_exception(const std::string& msg, const std::string& file_name)
		: msg(msg), file_name(file_name)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}
};

_IMPLEMENT_END