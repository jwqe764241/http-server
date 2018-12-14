#include "server/server.hpp"

_IMPLEMENT_SCOPE

server::server(): 
	acceptor(io_service),
	listen_socket(io_service),
	signal(io_service)
{
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
		std::cout << "Yeah" << std::endl;

		auto sock = std::move(listen_socket);
		//auto sock(std::move(std::move(listen_socket)));
	}

	//ready the next request
	acceptor.async_accept(listen_socket, std::bind(&server::on_accept, this, std::placeholders::_1));
}

void server::on_stop(const asio::error_code error_code)
{
	acceptor.close();
}


void server::start(server_option option)
{
	//TODO: should set localhost and 8080 port when ip and port are not specified.
	asio::ip::tcp::resolver resolver(io_service);
	asio::ip::tcp::resolver::query query({option["IP"], option["PORT"]});

	asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	acceptor.open(endpoint.protocol());
	acceptor.bind(endpoint);
	acceptor.listen(asio::socket_base::max_connections);

	acceptor.async_accept(listen_socket, std::bind(&server::on_accept, this, std::placeholders::_1));

	std::cout << "Now, server is running...." << std::endl;

	run();
}

void server::exit()
{
	signal.async_wait(std::bind(&server::on_stop, this, std::placeholders::_1));
	io_service.stop();
}

_IMPLEMENT_END