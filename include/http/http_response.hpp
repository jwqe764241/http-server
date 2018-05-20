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
		//First line data - HTTP verison, Response code, Describe
		std::string http_version;
		std::string response_code;
		std::string describe;

		//Additional header data
		std::map<std::string, std::string> header;
		//Body data
		std::string body;
	public:
		response();
		response(
			std::string http_version, 
			std::string response_code, 
			std::string describe);
		virtual ~response();

		//Get option into std::string
		std::string string();
		std::string operator[](const std::string key);
		//Add additional header data
		void add(const std::string key, const std::string value);
	};

}

_IMPLEMENT_END