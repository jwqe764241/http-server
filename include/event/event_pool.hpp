#pragma once

#include "event/circular_queue.hpp"


template <typename t_event>
class event_pool
{
private:
	circular_queue<t_event> queue;

public:
};

