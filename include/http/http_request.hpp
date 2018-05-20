#pragma once

#include <map>
#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "http/http.hpp"
#include "utils/utils.hpp"

#include "exceptions/parse_exception.hpp"

_IMPLEMENT_SCOPE

namespace http{

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

		//Get option into std::string
		std::string operator[](const std::string& key);
		void parse(const std::string& http_request);
		//Add additional header data
		void add(const std::string key, const std::string value);

	};

}

_IMPLEMENT_END