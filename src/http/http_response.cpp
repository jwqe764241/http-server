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
			data_stream << std::endl << body << std::endl;
		}

		return data_stream.str();
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
}

_IMPLEMENT_END