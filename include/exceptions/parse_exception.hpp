#pragma once

#include <string>
#include <exception>

#include "utils/utils.hpp"

using namespace std;

_IMPLEMENT_SCOPE

class parse_exception : public exception
{
private:
	string msg;

public:
	parse_exception(const string& msg)
		: msg(msg)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}
};

_IMPLEMENT_END