#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include "asio.hpp"
#include "http/http.hpp"
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "event/event.hpp"
#include "file/path.hpp"

#include "exceptions/parse_exception.hpp"
#include "exceptions/file_not_found_exception.hpp"

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
		server::http::request request;

		//parse request
		try
		{
			char buff[4096] = { 0 };
			socket.read_some(asio::buffer(buff));

			request.parse(buff);
		}
		catch(const server::parse_exception& e)
		{
			server::http::response response(
				"Unknown",
				std::to_string(server::http::BAD_REQUEST),
				"Bad Request");

			response.body = "Bad Request";

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}

		//send response
		try
		{
			path request_path(request.url);

			std::ifstream read_stream(request.url);

			//if file doesn't exist
			if(!read_stream)
			{
				throw server::file_not_found_exception("File doesn't exist", request.url);
			}

			server::http::response response(
				request.version, 
				std::to_string(server::http::OK), 
				"OK");

			/*
				get file data here
			*/
			
			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
		catch (const server::file_not_found_exception& e)
		{
			server::http::response response(
				request.version,
				std::to_string(server::http::NOT_FOUND),
				"Not Found");

			response.body = "Not Found";

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
		catch (const std::exception& e)
		{
			server::http::response response(
				request.version,
				std::to_string(server::http::INTERNAL_SERVER_ERROR), 
				"Internal Server Error");

			response.body = "Internal Server Error";

			socket.write_some(asio::buffer(response.string()));
			socket.close();

			throw e;
		}
		
	}
};