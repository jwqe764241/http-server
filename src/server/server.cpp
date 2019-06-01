#include "server/server.hpp"

_IMPLEMENT_SCOPE

server::server(int worker_number, int max_task)
	: acceptor(io_service),
	listen_socket(io_service),
	signal(io_service),
	event_pool(worker_number, max_task),
	logger(std::cout)
{
	this->worker_number = worker_number;
	this->max_task = max_task;
}

server::~server()
{
	stop();
}

void server::run()
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

void server::on_accept(const asio::error_code error_code)
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
			logger.error(e.what());
		}
	}
	else
	{
		logger.error(error_code.value() +  " : " + error_code.message());
	}

	listen_socket.close();
	acceptor.async_accept(listen_socket, std::bind(&server::on_accept, this, std::placeholders::_1));
}

void server::on_stop(const asio::error_code error_code)
{
	event_pool.stop();
	acceptor.close();
}

void server::start(std::string ip, std::string port, std::string root_path)
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
		logger.error(e.what());
		return;
	}

	this->root_path = root_path;

	acceptor.async_accept(listen_socket, std::bind(&server::on_accept, this, std::placeholders::_1));

	logger << "Server configured" << "\n";
	logger << "  ip : " << ip << "\n";
	logger << "  port : " << port << "\n";
	logger << "  root path : " << root_path << "\n";
	logger << "  workers : " << worker_number << "\n";
	logger << "  max task : " << max_task << "\n\n";

	logger.info("Now, server is running....");

	run();
}

void server::stop()
{
	signal.async_wait(std::bind(&server::on_stop, this, std::placeholders::_1));
	io_service.stop();
}

std::string server::get_root_path()
{
	return root_path;
}

_IMPLEMENT_END