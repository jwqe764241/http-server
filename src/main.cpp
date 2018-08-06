#include <stdlib.h>
#include <limits>

#include <server/server.hpp>

#include "http/http_request.hpp"

#include "event/dispatcher.hpp"
#include "event/basic_events.hpp"

int main(int argc, char ** argv)
{
	
	server::server server;

	server::option::basic_option<std::string, std::string> server_option;
		server_option.add(std::pair<std::string, std::string>("IP", "172.30.1.3"));
		server_option.add(std::pair<std::string, std::string>("PORT", "45000"));

	server.start(server_option);
	


	system("pause");
	return 0;
}