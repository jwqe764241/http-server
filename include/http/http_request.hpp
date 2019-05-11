#pragma once

#include <map>
#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "utils/utils.hpp"
#include "exceptions/parse_exception.hpp"

_IMPLEMENT_SCOPE

namespace http
{
	struct request
	{
	public:
		//First line data - Reqeust method, Request URL, HTTP version
		std::string method;
		std::string url;
		std::string version;

		//Additional header data
		std::map<std::string, std::string> header;
		//Body data
		std::string body;
			
	public:
		request();
		request(const std::string& http_request);
		virtual ~request();

		void parse(const std::string& http_request);
		//Add additional header data
		void set_header(const std::string& key, const std::string& value);
		void set_header(const std::map<std::string, std::string>& header);

		std::string get_header(const std::string& key);
		const std::map<std::string, std::string>& get_header();
	};
}

_IMPLEMENT_END