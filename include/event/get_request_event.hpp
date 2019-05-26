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
	get_request_event(asio::io_service& service, asio::ip::tcp::socket socket);
	~get_request_event();

	virtual void notify() override;

	void do_get(web::http::request request);
	void do_post(web::http::request request);
};