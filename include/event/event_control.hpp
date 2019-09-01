#pragma once

#include <string>
#include <memory>
#include <map>
#include <functional>
#include <initializer_list>

#include "event/event.hpp"

class event_control
{
public:
	using generator_function = std::function<std::shared_ptr<event>()>;
	using event_control_pair = std::pair<std::string, generator_function>;

private:
	std::map<std::string, generator_function> list;

public:
	event_control();
	event_control(std::initializer_list<event_control_pair> controls);

	void add_control(std::string url, generator_function handler);
	void add_control(event_control_pair pair);

	std::shared_ptr<event> get_event_handler(std::string url);
};