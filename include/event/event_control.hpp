#pragma once

#include <string>
#include <memory>
#include <map>
#include <functional>
#include <initializer_list>

#include "event/event.hpp"

using handler_function = std::function<std::shared_ptr<event>()>;
using event_control_pair = std::pair<std::string, handler_function>;

class event_control
{
private:
	std::map<std::string, handler_function> list;

public:
	event_control();
	event_control(std::initializer_list<event_control_pair> controls);

	void add_control(std::string url, handler_function handler);
	void add_control(event_control_pair pair);

	std::shared_ptr<event> get_event_handler(std::string url);
};