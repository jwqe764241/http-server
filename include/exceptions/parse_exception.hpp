#pragma once

#include <string>
#include <exception>

#include "utils/utils.hpp"

_IMPLEMENT_SCOPE

class parse_exception : public std::exception
{
private:
	std::string msg;


public:
	parse_exception(const std::string& msg)
		: msg(msg)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}

};

_IMPLEMENT_END