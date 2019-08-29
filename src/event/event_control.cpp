#include "event/event_control.hpp"

event_control::event_control()
{
}

event_control::event_control(std::initializer_list<event_control_pair> controls)
{
	list.insert(controls.begin(), controls.end());
}

void event_control::add_control(std::string url, handler_function handler)
{
	add_control({ url, handler });
}

void event_control::add_control(event_control_pair pair)
{
	list.insert(pair);
}

std::shared_ptr<event> event_control::get_event_handler(std::string url)
{
	return list[url]();
}