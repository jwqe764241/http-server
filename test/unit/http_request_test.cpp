#ifdef __MINGW32__
	#define __USE_MINGW_ANSI_STDIO 0
#endif

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "http/http_request.hpp"


//g++ -o test.exe unit/http_request_test.cpp -I../lib -I../include -B../src --std c++14

TEST_CASE("http request parse test 1", "[parse]")
{
	std::string request_string = R"aaa(GET / HTTP/1.1
Host : 127.0.0.1
Connection : keep - alive
Purpose : prefetch)aaa";
			
	server::http::request request(request_string);
	
	REQUIRE(request.method == "GET");
	REQUIRE(request.url == "/");
	REQUIRE(request.version == "HTTP/1.1");
	
	REQUIRE(request["Host"] == "127.0.0.1");
	REQUIRE(request["Connection"] == "keep - alive");
	REQUIRE(request["Purpose"] == "prefetch");
}

TEST_CASE("http request parse test 2", "[parse]")
{
	std::string request_string = R"aaa(GET /favicon.ico HTTP/1.1
Host : 127.0.0.1
Connection : keep - alive
Purpose : prefetch)aaa";
			
	server::http::request request(request_string);
	
	REQUIRE(request.method == "GET");
	REQUIRE(request.url == "/favicon.ico");
	REQUIRE(request.version == "HTTP/1.1");
	
	REQUIRE(request["Host"] == "127.0.0.1");
	REQUIRE(request["Connection"] == "keep - alive");
	REQUIRE(request["Purpose"] == "prefetch");
}