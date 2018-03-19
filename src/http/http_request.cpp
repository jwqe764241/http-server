#include "http/http_request.hpp"

_IMPLEMENT_SCOPE

namespace http
{

	request::request()
	{
	}

	request::request(std::string http_request)
	{
	}

	std::string request::operator[](std::string key)
	{
		return std::string();
	}

	void request::parse(std::string http_request)
	{
	}

	void request::add(std::string key, std::string value)
	{
	}

}

_IMPLEMENT_END