#pragma once

#include <map>
#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "http/http.hpp"
#include "utils/utils.hpp"

#include "exceptions/parse_exception.hpp"

using namespace std;

_IMPLEMENT_SCOPE

namespace http
{

	using header = map<string, string>;

	//대충 요청 예제
	//GET / favicon.ico HTTP / 1.1
	//Host: 127.0.0.1 : 5000
	//Connection : keep - alive
	//User - Agent : Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 64.0.3282.186 Safari / 537.36
	//Accept : image / webp, image / apng, image/*,*/*; q = 0.8
	//Referer: http://127.0.0.1:5000/
	//Accept - Encoding : gzip, deflate, br
	//Accept - Language : ko - KR, ko; q = 0.9, en - US; q = 0.8, en; q = 0.7, zh - CN; q = 0.6, zh; q = 0.5
	//n; q = 0.7, zh - CN; q = 0.6, zh; q = 0.5

	struct request
	{
	public:
		string method;
		string url;
		string version;

		header header;
		string body;
			
	public:
		request();
		request(const string& http_request);

		string operator[](const string& key);
		void parse(const string& http_request);
		void add(const string key, const string value);

	};

}

_IMPLEMENT_END