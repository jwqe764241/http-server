#pragma once

#include <iostream>

#include "asio.hpp"
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "exceptions/parse_exception.hpp"
#include "event/event.hpp"

class get_request_event : public event
{
private:
	asio::ip::tcp::socket socket;

public:
	get_request_event() = delete;

	get_request_event(asio::io_service& service, asio::ip::tcp::socket socket)
		: socket(std::move(socket))                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	{
	}

	~get_request_event()
	{
		std::cout << "Event Destroyed" << std::endl;
	}

	virtual void notify() override
	{
		try
		{
			char buff[4096] = {0};
			socket.read_some(asio::buffer(buff));

			server::http::request request(buff);

			server::http::response response("HTTP/1.1", "200", "OK");
			response.body = "<html><head><title>ass shit fuck yeah</title></head><h1>Fuck You asshole</h1><body></body></html>";

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
		catch (const server::parse_exception& e)
		{
			std::cout << e.what() << std::endl;
			socket.close();
		}
		catch (const std::exception& e)
		{
			throw e;
		}
		
	}
};