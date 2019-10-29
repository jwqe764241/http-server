#include "http/http_response.hpp"

_IMPLEMENT_SCOPE

namespace http
{
	response::response()
	{
	}

	response::response(
		std::string version,
		std::string code,
		std::string describe)
	{
		this->version = version;
		this->code = code;
		this->describe = describe;
	}

	response::~response()
	{
	}

	void response::set_header(const std::string& key, const std::string& value)
	{
		header[key] = value;
	}

	void response::set_header(const std::map<std::string, std::string>& header)
	{
		this->header = header;
	}

	std::string response::get_header(const std::string& key)
	{
		return header[key];
	}

	const std::map<std::string, std::string>& response::get_header()
	{
		return header;
	}

	std::string response::to_string()
	{
		std::ostringstream data_stream;

		//First line data can't be a null
		if (version.empty() && code.empty() && describe.empty())
			throw parse_exception("Start line data can't be a null, check the startline data");

		data_stream << version << character::WHITESPACE
			<< code << character::WHITESPACE << describe << std::endl;

		for (const auto& pair : header)
		{
			data_stream << pair.first << ":" << pair.second << std::endl;
		}

		if (!body.empty())
		{
			//Insert empty line first because body data seperated with line
			data_stream << std::endl << body << std::endl;
		}

		return data_stream.str();
	}
}

_IMPLEMENT_END