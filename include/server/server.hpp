#pragma once

#include <csignal>
#include <memory>
#include <iostream>

#include "asio.hpp"
#include "utils/utils.hpp"
#include "utils/basic_option.hpp"
#include "utils/logger.hpp"
#include "event/event.hpp"
#include "event/get_request_event.hpp"
#include "event/thread_pool.hpp"

_IMPLEMENT_SCOPE

class server
{
	logger::logger logger;

private:
	asio::io_service io_service;
	asio::signal_set signal;
	asio::ip::tcp::socket listen_socket;
	asio::ip::tcp::acceptor acceptor;

	thread_pool<std::shared_ptr<event>> event_pool;

private:
	//accept connection and reday to communication
	void run();

	void on_accept(const asio::error_code error_code);
	void on_stop(const asio::error_code error_code);

public:
	//initialize server with default option
	server(int max_worker, int max_task);
	virtual ~server();

	//Not allow assign, copy, move
	server(const server& server) = delete;
	server(server&& server) = delete;
	server& operator=(const server& server) = delete;

	//server start end function
	//get all resource
	void start(std::string ip, std::string port);
	//release all resource
	void stop();
};

_IMPLEMENT_END