#pragma once

#include <sstream>
#include <string>

#include "http/http.hpp"
#include "utils/utils.hpp"

#include "exceptions/parse_exception.hpp"

_IMPLEMENT_SCOPE

namespace http{

	struct response
	{
	public:
		//시작줄
		std::string http_version;
		std::string response_code;
		std::string describe;

		//부가 헤더 정보 추가
		header header;
		std::string body;
	public:
		response();
		response(
			std::string http_version, 
			std::string response_code, 
			std::string describe);
		~response();

		//std::string 문자열로 변경
		std::string string();
		std::string operator[](const std::string key);
		//부가 헤더 정보 추가
		void add(const std::string key, const std::string value);
	};

}

_IMPLEMENT_END