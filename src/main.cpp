#include "get_option.hpp"
#include "server/server.hpp"
#include "utils/file_option.hpp"

int main(int argc, char** argv)
{
	using namespace cmd;

	parser parser(argc, argv, {
		option("--option", "-o", 1),
		option("--ip", "-i", 1),
		option("--port", "-p", 1),
		option("--root", "-r", 1),
		option("--worker", "-w", 1),
		option("--task", "-t", 1)
	});

	if (parser.has_option("--option"))
	{
		file_option option;

		try
		{
			option = file_option(std::ifstream(parser.get_arguments("--option")[0]));
		}
		catch (const std::ifstream::failure& e)
		{
			std::cout << "No option file or cannot access to option file," << "\n";
			std::cout << "Will use default options instead." << "\n\n";
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		try
		{
			web::server server(
				option.has("workers") ? std::stoi(option["workers"]) : 1,
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
	}
	else
	{
		try
		{
			web::server server(
				parser.has_option("--worker") ? std::stoi(parser.get_arguments("--worker")[0]) : 1,
				parser.has_option("--task") ? std::stoi(parser.get_arguments("--task")[0]) : 200);

			server.start(
				parser.has_option("--ip") ? parser.get_arguments("--ip")[0] : "127.0.0.1",
				parser.has_option("--port") ? parser.get_arguments("--port")[0] : "8080",
				parser.has_option("--root") ? parser.get_arguments("--root")[0] : "./");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	system("pause");
	return 0;
}