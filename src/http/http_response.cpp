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

		//시작줄 데이터는 null 불가
		if(http_version.empty() && response_code.empty() && describe.empty())
			throw parse_exception("startline data can't be a null, check the startline data");

		data_stream << http_version << global::WHITESPACE
					<< response_code << global::WHITESPACE
					<< describe << std::endl;

		//부가 헤더 정보
		for(const auto& pair : header)
		{
			data_stream << pair.first << ":" << pair.second << std::endl;
		}

		//바디 데이터
		if(!body.empty())
		{
			data_stream << std::endl << body << std::endl;
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