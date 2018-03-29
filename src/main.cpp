#include <iostream>
#include <string>

#include "http/http_request.hpp"

int main(int argc, char ** argv)
{
	std::string request_test = R"end(GET / favicon.ico HTTP / 1.1
Host: 127.0.0.1 : 5000
Connection : keep - alive
User - Agent : Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 64.0.3282.186 Safari / 537.36
Accept : image / webp, image / apng, image/*,*/*; q = 0.8
Referer: http:127.0.0.1:5000/
Accept - Encoding : gzip, deflate, br
Accept - Language : ko - KR, ko; q = 0.9, en - US; q = 0.8, en; q = 0.7, zh - CN; q = 0.6, zh; q = 0.5 n; q = 0.7, zh - CN; q = 0.6, zh; q = 0.5
)end";

	server::http::request parsed_request(request_test);

	for(std::pair<std::string, std::string> item : parsed_request.header)
	{
		std::cout << item.first << "||" << item.second << std::endl;
	}

	system("pause");

	return 0;
}