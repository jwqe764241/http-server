#ifdef __MINGW32__
	#define __USE_MINGW_ANSI_STDIO 0
#endif

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "http/http_response.hpp"

TEST_CASE("http response build test 1", "[build]")
{
	std::string expected_string = R"aaa(HTTP/1.1 200 OK
Connection:keep - alive
Host:127.0.0.1
Purpose:prefetch)aaa";
	
	server::http::response response("HTTP/1.1", "200", "OK");
	response.add("Connection", "keep - alive");
	response.add("Host", "127.0.0.1");
	response.add("Purpose", "prefetch");
	
	REQUIRE(expected_string == response.string());
}

TEST_CASE("http response build test 2", "[build]")
{
	std::string expected_string = R"aaa(HTTP/1.1 404 NOT FOUND
Connection:keep - alive
Host:127.0.0.1
Purpose:prefetch)aaa";
	
	server::http::response response("HTTP/1.1", "404", "NOT FOUND");
	response.add("Connection", "keep - alive");
	response.add("Host", "127.0.0.1");
	response.add("Purpose", "prefetch");
	
	REQUIRE(expected_string == response.string());
}