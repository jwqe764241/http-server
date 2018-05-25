#pragma once

#include <string>
#include <exception>

#include "utils/utils.hpp"

_IMPLEMENT_SCOPE

class parse_exception : public std::exception
{
private:
	std::string msg;
	int id;

	enum ID
	{

	};

public:
	parse_exception(const std::string& msg, int id)
		: msg(msg), id(id)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}

	int id() const noexcept
	{
		return id;
	}
};

_IMPLEMENT_END