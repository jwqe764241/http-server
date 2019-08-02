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
		std::string worker;
		try
		{
			if (parser.has_option("--worker"))
			{
				worker = parser.get_arguments("--worker").at(0);
			}
			else
			{
				worker = "1";
			}
		}
		catch (const std::exception& e)
		{
			worker = "1";
		}

		std::string task;
		try
		{
			if (parser.has_option("--task"))
			{

				task = parser.get_arguments("--task").at(0);
			}
			else
			{
				task = "200";
			}
		}
		catch (const std::exception& e)
		{
			task = "200";
		}

		std::string ip;
		try
		{
			if (parser.has_option("--ip"))
			{
				ip = parser.get_arguments("--ip").at(0);
			}
			else
			{
				std::cout << "err : ip not served" << "\n";

				return 0;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "err : ip not served" << "\n";

			return 0;
		}

		std::string port;
		try
		{
			if (parser.has_option("--port"))
			{
				port = parser.get_arguments("--port").at(0);
			}
			else
			{
				std::cout << "err : port not served" << "\n";

				return 0;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "err : port not served" << "\n";

			return 0;
		}

		std::string root;
		try
		{
			if (parser.has_option("--root"))
			{
				root = parser.get_arguments("--root").at(0);
			}
			else
			{
				std::cout << "err : root path not served" << "\n";

				return 0;
			}
		}
		catch (const std::exception& e)
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