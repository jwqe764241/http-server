#include "event/get_request_event.hpp"

get_request_event::get_request_event(asio::io_service& service, asio::ip::tcp::socket socket, server::server* server)
	: socket(std::move(socket)), server(server)
{
}

get_request_event::~get_request_event()
{
}

void get_request_event::notify()
{
	server::http::request request;

	//parse request
	try
	{
		char buff[4096] = { 0 };
		socket.read_some(asio::buffer(buff));

		request.parse(buff);
	}
	catch (const server::parse_exception& e)
	{
		std::string status_string = server::http::get_status_string(server::http::BAD_REQUEST);

		server::http::response response(
			utils::HTTP_VERSION,
			std::to_string(server::http::BAD_REQUEST),
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
		std::string status_string = server::http::get_status_string(server::http::METHOD_NOT_ALLOWED);

		server::http::response response(
			utils::HTTP_VERSION,
			std::to_string(server::http::METHOD_NOT_ALLOWED),
			status_string);

		response.body = status_string;

		socket.write_some(asio::buffer(response.string()));
		socket.close();
	}
}

void get_request_event::do_get(server::http::request request)
{
	do_post(request);
}

void get_request_event::do_post(server::http::request request)
{
	//send response
	try
	{
		path path(request.url);

		content request_content(server->get_root_path());
			request_content.append(content(path.get_real_path_string()));

		auto remote = socket.remote_endpoint();

		std::cout << "requested : " << remote.address().to_string() << ":" << remote.port() << " " << request_content.get_path() << std::endl;

		std::ifstream read_stream = request_content.get_stream();

		//if file doesn't exist
		if (!read_stream)
		{
			throw server::file_not_found_exception("File doesn't exist", request.url);
		}

		std::string status_string = server::http::get_status_string(server::http::OK);

		server::http::response response(
			utils::HTTP_VERSION,
			std::to_string(server::http::OK),
			status_string);

		/*
			get file data here
		*/
		std::stringstream file_stream;
		file_stream << read_stream.rdbuf();
		response.body = file_stream.str();

		response.set_header("Content-Type", request_content.get_type());

		socket.write_some(asio::buffer(response.string()));
		socket.close();
	}
	catch (const server::file_not_found_exception& e)
	{
		std::string status_string = server::http::get_status_string(server::http::NOT_FOUND);

		server::http::response response(
			utils::HTTP_VERSION,
			std::to_string(server::http::NOT_FOUND),
			status_string);

		response.body = status_string;

		socket.write_some(asio::buffer(response.string()));
		socket.close();
	}
	catch (const std::exception& e)
	{
		std::string status_string = server::http::get_status_string(server::http::INTERNAL_SERVER_ERROR);

		server::http::response response(
			utils::HTTP_VERSION,
			std::to_string(server::http::INTERNAL_SERVER_ERROR),
			status_string);

		response.body = status_string;

		socket.write_some(asio::buffer(response.string()));
		socket.close();

		throw e;
	}
}