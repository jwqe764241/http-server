#include "server/http_server.hpp"

_IMPLEMENT_SCOPE

http_server::http_server(int worker_number, int max_task)
	: acceptor(io_service),
	listen_socket(io_service),
	signal(io_service),
	event_pool(worker_number, max_task),
	log(std::make_unique<logging::console_logger>(logging::LEVEL::INFO | logging::LEVEL::FATAL))
{
	if (worker_number < 1)
	{
		throw std::invalid_argument("worker number must be more than 1");
	}
	else if (max_task < 1)
	{
		throw std::invalid_argument("max task number must be more than 1");
	}

	this->worker_number = worker_number;
	this->max_task = max_task;
}

http_server::~http_server()
{
	stop();
}

void http_server::run()
{
	try
	{
		io_service.run();
	}
	catch (const std::exception& e)
	{
		//...
	}
	catch (...)
	{
		//...
	}
}

void http_server::on_accept(const asio::error_code error_code)
{
	if(!acceptor.is_open())
	{
		return;
	}
	
	if(!error_code)
	{
		try
		{
			event_pool.push_task(std::make_shared<get_request_event>(io_service, std::move(listen_socket), this));
		}
		catch(std::exception& e)
		{
			log->write(logging::LEVEL::FATAL, e.what());
		}
	}
	else
	{
		log->write(logging::LEVEL::FATAL, error_code.value() + " : " + error_code.message());
		listen_socket.close();
	}
	acceptor.async_accept(listen_socket, std::bind(&http_server::on_accept, this, std::placeholders::_1));
}

void http_server::on_stop(const asio::error_code error_code)
{
	event_pool.stop();
	acceptor.close();
}

void http_server::start(std::string ip, std::string port, std::string root_path)
{
	asio::ip::tcp::resolver resolver(io_service);
	asio::ip::tcp::resolver::query query({ip, port});

	asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	try
	{
		acceptor.open(endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen(asio::socket_base::max_connections);
	}
	catch (const std::exception & e)
	{
		log->write(logging::LEVEL::FATAL, e.what());
		return;
	}

	this->root_path = root_path;

	acceptor.async_accept(listen_socket, std::bind(&http_server::on_accept, this, std::placeholders::_1));

	log->write(logging::LEVEL::INFO, "Server configured");
	log->write(logging::LEVEL::INFO, "  ip : " + ip);
	log->write(logging::LEVEL::INFO, "  port : " + port);
	log->write(logging::LEVEL::INFO, "  root path : " + root_path);
	log->write(logging::LEVEL::INFO, "  workers : " + std::to_string(worker_number));
	log->write(logging::LEVEL::INFO, "  max task : " + std::to_string(max_task));

	log->write(logging::LEVEL::INFO, "Now, server is running....\n\n");

	run();
}

void http_server::stop()
{
	signal.async_wait(std::bind(&http_server::on_stop, this, std::placeholders::_1));
	io_service.stop();
}

std::string http_server::get_root_path()
{
	return root_path;
}

_IMPLEMENT_END