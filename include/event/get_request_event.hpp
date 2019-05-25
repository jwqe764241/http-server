#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <string>

#include "asio.hpp"
#include "http/http.hpp"
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "event/event.hpp"
#include "file/content.hpp"
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
	}

	virtual void notify() override
	{
		web::http::request request;

		//parse request
		try
		{
			char buff[4096] = { 0 };
			socket.read_some(asio::buffer(buff));

			request.parse(buff); 
		}
		catch(const web::parse_exception& e)
		{
			std::string status_string = web::http::get_status_string(web::http::BAD_REQUEST);

			web::http::response response(
				"Unknown",
				std::to_string(web::http::BAD_REQUEST),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}

		//TODO: change
		if (request.method == "GET")
		{
			do_get(request);
		}
		else if (request.method == "POST")
		{
			do_post(request);
		}
		else
		{
			std::string status_string = web::http::get_status_string(web::http::METHOD_NOT_ALLOWED);

			web::http::response response(
				request.version,
				std::to_string(web::http::METHOD_NOT_ALLOWED),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
	}

	void do_get(web::http::request request)
	{
		do_post(request);
	}

	void do_post(web::http::request request)
	{
		//send response
		try
		{
			content content("C:\\a" + request.url);
			std::ifstream read_stream = content.get_stream();

			//if file doesn't exist
			if (!read_stream)
			{
				throw web::file_not_found_exception("File doesn't exist", request.url);
			}

			std::string status_string = web::http::get_status_string(web::http::OK);

			web::http::response response(
				request.version,
				std::to_string(web::http::OK),
				status_string);

			/*
				get file data here
			*/
			std::stringstream file_stream;
			file_stream << read_stream.rdbuf();
			response.body = file_stream.str();

			response.set_header("Content-Type", content.get_type());

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
		catch (const web::file_not_found_exception& e)
		{
			std::string status_string = web::http::get_status_string(web::http::NOT_FOUND);

			web::http::response response(
				request.version,
				std::to_string(web::http::NOT_FOUND),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
		catch (const std::exception& e)
		{
			std::string status_string = web::http::get_status_string(web::http::INTERNAL_SERVER_ERROR);

			web::http::response response(
				request.version,
				std::to_string(web::http::INTERNAL_SERVER_ERROR),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();

			throw e;
		}
	}
};