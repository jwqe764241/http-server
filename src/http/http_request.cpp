#include "http/http_request.hpp"

_IMPLEMENT_SCOPE

namespace http
{

	request::request()
	{
	}

	request::request(const std::string& http_request)
	try
	{
		parse(http_request);
	}
	catch(const parse_exception& e)
	{
		std::cout << "parse error : " << e.what << std::endl;

		throw e;
	}

	std::string request::operator[](const std::string& key)
	{

		return std::string();
	}

	void request::parse(const std::string& http_request)
	{	
		if(http_request.empty())
			throw parse_exception("HTTP request is empty. Check that request");


		if(http_request.find(global::LINE_CHANGE, 0) != std::string::npos)
		{

		}

	}

	void request::add(const std::string& key, const std::string& value)
	{
	}

}

_IMPLEMENT_END