#include "server/server.hpp"

_IMPLEMENT_SCOPE

server::server(int max_worker, int max_task)
	: acceptor(io_service),
	listen_socket(io_service),
	signal(io_service),
	event_pool(max_worker, max_task),
	logger(std::cout)
{
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
			//TODO: fix lifetime of event. when flow exit from this function, event will be destroyed
			event_pool.push_task(std::make_shared<get_request_event>(io_service, std::move(listen_socket)));
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
	//TODO: should set localhost and 8080 port when ip and port are not specified.
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