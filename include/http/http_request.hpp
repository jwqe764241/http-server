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
		//시작줄
		std::string method;
		std::string url;
		std::string version;

		//부가 헤더 정보
		header header;
		std::string body;
			
	public:
		request();
		request(const std::string& http_request);
		~request();

		std::string operator[](const std::string& key);
		void parse(const std::string& http_request);
		//부가 헤더 정보 추가
		void add(const std::string key, const std::string value);

	};

}

_IMPLEMENT_END