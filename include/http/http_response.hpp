#pragma once

#include <map>
#include <sstream>
#include <string>

#include "utils/utils.hpp"
#include "exceptions/parse_exception.hpp"

_IMPLEMENT_SCOPE

namespace http
{
	struct response
	{
	public:
		//First line data - HTTP verison, Response code, Describe
		std::string version;
		std::string code;
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

		//Add additional header data
		void set_header(const std::string& key, const std::string& value);
		void set_header(const std::map<std::string, std::string>& header);

		std::string get_header(const std::string& key);
		const std::map<std::string, std::string>& get_header();

		std::string to_string();
	};
}

_IMPLEMENT_END