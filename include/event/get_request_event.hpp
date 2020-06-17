#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <string>

#include "asio.hpp"
#include "server/server.hpp"
#include "http/http.hpp"
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "event/event.hpp"
#include "file/content.hpp"
#include "exceptions/parse_exception.hpp"
#include "exceptions/file_not_found_exception.hpp"

namespace server { class http_server; }

class get_request_event : public event
{
private:
	asio::ip::tcp::socket socket;
	server::http_server* server = nullptr;

public:
	get_request_event() = delete;
	get_request_event(asio::io_service& service, asio::ip::tcp::socket socket, server::http_server* server);
	~get_request_event();

	virtual void notify() override;

	void do_get(server::http::request request);
	void do_post(server::http::request request);
};