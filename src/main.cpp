#include "server/server.hpp"
#include "utils/file_option.hpp"

int main(int argc, char ** argv)
{
	file_option option;

	try
	{
		option = file_option(std::ifstream("TestOption.opt"));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		web::server server(
			option.has("worker") ? std::stoi(option["worker"]) : 1,
			option.has("max_task") ? std::stoi(option["max_task"]) : 200);

		server.start(
			option.has("ip") ? option["ip"] : "127.0.0.1",
			option.has("port") ? option["port"] : "8080",
			option.has("root_path") ? option["root_path"] : "./");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}
