#include "event/get_request_event.hpp"

get_request_event::get_request_event(asio::io_service& service, asio::ip::tcp::socket socket, web::server* server)
	: socket(std::move(socket)), server(server)
{
}

get_request_event::~get_request_event()
{
}

void get_request_event::notify()
{
	web::http::request request;

	//parse request
	try
	{
		char buff[4096] = { 0 };
		socket.read_some(asio::buffer(buff));

		request.parse(buff);
	}
	catch (const web::parse_exception& e)
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

void get_request_event::do_get(web::http::request request)
{
	do_post(request);
}

void get_request_event::do_post(web::http::request request)
{
	//send response
	try
	{
		content content(server->get_root_path() + request.url);
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