#pragma once

#include <iostream>

#include "asio.hpp"

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

	virtual void notify() override
	{
		try
		{
			char buff[4096] = {0};

			socket.read_some(asio::buffer(buff));

			std::cout << "received data : " << buff << std::endl;

		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		
	}
};