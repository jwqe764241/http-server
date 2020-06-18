#include "get_option.hpp"
#include "server/http_server.hpp"
#include "utils/file_option.hpp"

std::string get_value_if_exist(cmd::parser& parser, std::string opt, std::string fail_value);

int main(int argc, char** argv)
{
	using namespace cmd;

	/*
		options

		--option (-o) : option file path, if this option served, another option will be ignored
		--ip     (-i) : server ip
		--port   (-p) : server port
		--root   (-r) : server resource root path
		--worker (-w) : server worker number
		--task   (-t) : server task queue size
		--help   (-h) : show help
	*/
	parser parser(argc, argv, {
		option("--option", "-o", 1),
		option("--ip", "-i", 1),
		option("--port", "-p", 1),
		option("--root", "-r", 1),
		option("--worker", "-w", 1),
		option("--task", "-t", 1),
		option("--help", "-h")
	});

	if (parser.has_option("--help"))
	{
		std::cout << "Usage\n";
		std::cout << "\t<server> -o <option path> : start server with option file\n";
		std::cout << "\t<server> -i <ip> -p <port> -r <path> -w <number> -t <size> : start server\n\n\n";
		std::cout << "Options\n";
		std::cout << "\t -o (--option)\t option file path\n";
		std::cout << "\t -i (--ip)\t server ip (required)\n";
		std::cout << "\t -p (--port)\t server port (required)\n";
		std::cout << "\t -r (--root)\t server resource root path(required)\n";
		std::cout << "\t -w (--worker)\t server worker number (default - 1)\n";
		std::cout << "\t -t (--task)\t server task queue size (default - 200)\n" << std::endl;
	}
	else if (parser.has_option("--option"))
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
			server::http_server server(
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
	else if(parser.has_option("--ip") || parser.has_option("--port") || parser.has_option("--root"))
	{
		try
		{
			std::string worker = get_value_if_exist(parser, "--worker", "1");
			std::string task = get_value_if_exist(parser, "--task", "200");
			std::string ip = parser.get_arguments("--ip").front();
			std::string port = parser.get_arguments("--port").front();
			std::string root = parser.get_arguments("--root").front();

			server::http_server server(std::stoi(worker), std::stoi(task));
			server.start(ip, port, root);
		}
		catch (const cmd::option_not_found_exception& e)
		{
			const std::string& option_name = e.get_option();

			if (option_name == "--ip")
			{
				std::cout << "err : ip not served" << "\n";
			}
			else if (option_name == "--port")
			{
				std::cout << "err : port not served" << "\n";
			}
			else if (option_name == "--root")
			{
				std::cout << "err : root path not served" << "\n";
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Unknown commands. --help or -h to show all commands." << std::endl;
	}

	return 0;
}

std::string get_value_if_exist(cmd::parser& parser, std::string opt, std::string fail_value)
{
	try
	{
		if (parser.has_option(opt))
		{
			return parser.get_arguments(opt).front();
		}
		else
		{
			return fail_value;
		}
	}
	catch (const std::exception& e)
	{
		return fail_value;
	}
}