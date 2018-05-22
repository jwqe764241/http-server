#include "http/http_response.hpp"

_IMPLEMENT_SCOPE

namespace http{

	response::response()
	{
	}

	response::response(
		std::string http_version,
		std::string response_code,
		std::string describe)
	{
		this->http_version = http_version;
		this->response_code = response_code;
		this->describe = describe;
	}

	response::~response()
	{
	}

	std::string response::string()
	{
		std::ostringstream data_stream;

		//First line data can't be a null
		if(http_version.empty() && response_code.empty() && describe.empty())
			throw parse_exception("Start line data can't be a null, check the startline data");

		data_stream << http_version << global::WHITESPACE
					<< response_code << global::WHITESPACE
					<< describe << std::endl;

		//Additional header data
		for(const auto& pair : header)
		{
			data_stream << pair.first << ":" << pair.second << std::endl;
		}

		//Body data
		if(!body.empty())
		{
			//Insert empty line first because body data seperated with line
			data_stream << std::endl << body;
		}

		return data_stream.str();
	}

	std::string response::operator[](const std::string key)
	{
		return header[key];
	}

	void response::add(const std::string key, const std::string value)
	{
		header.insert(std::pair<std::string, std::string>(key, value));
	}
}

_IMPLEMENT_END