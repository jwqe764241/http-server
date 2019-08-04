#include "get_option.hpp"
#include "server/server.hpp"
#include "utils/file_option.hpp"

std::string get_value_if_exist(cmd::parser& parser, std::string opt, std::string fail_value)
{
	try
	{
		if (parser.has_option(opt))
		{
			return parser.get_arguments(opt).at(0);
		}
		else
		{
			return fail_value;
		}
	}
	catch (const std::exception & e)
	{
		return fail_value;
	}
}

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
			option = file_option(std::ifstream(parser.get_arguments("--option").at(0)));
		}
		catch (const std::ifstream::failure& e)
		{
			std::cout << "err : No option file or cannot access to option file"  << "\n";

			return 0;
		}
		catch (const std::out_of_range& e)
		{
			std::cout << "err : Option file path not served" << "\n";

			return 0;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;

			return 0;
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
		std::string worker = get_value_if_exist(parser, "--worker", "1");

		std::string task = get_value_if_exist(parser, "--task", "200");

		std::string ip = get_value_if_exist(parser, "--ip", "");
		if(ip == "")
		{
			std::cout << "err : ip not served" << "\n";

			return 0;
		}

		std::string port = get_value_if_exist(parser, "--port", "");
		if(port == "")
		{
			std::cout << "err : port not served" << "\n";

			return 0;
		}

		std::string root = get_value_if_exist(parser, "--root", "");
		if(root == "")
		{
			std::cout << "err : root path not served" << "\n";

			return 0;
		}

		try
		{
			web::server server(std::stoi(worker), std::stoi(task));
				server.start(ip, port, root);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	system("pause");
	return 0;
}