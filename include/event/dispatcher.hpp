#pragma once

#include <map>

template <typename t_event>
class dispatcher
{
private:
	std::vector<t_event> events;

public:
	dispatcher()
	{

	}

	~dispatcher()
	{
	
	}

	void attach(t_event event)
	{
		events.push_back(event);
	}

	void noify()
	{
		for(const t_event& e : events)
			e.notify();
	}
};
