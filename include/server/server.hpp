#pragma once

#include "utils/utils.hpp"
#include "asio.hpp"
#include "utils/basic_option.hpp"

_IMPLEMENT_SCOPE

class server
{
	using server_option = option::basic_option<std::string, std::string>;

private:
	server_option option;

public:
	server();
	server(server_option option);
	//Not allow assign, copy, move
	server(const server& server) = delete;
	server(server&& server) = delete;
	server& operator=(const server& server) = delete;



};

_IMPLEMENT_END