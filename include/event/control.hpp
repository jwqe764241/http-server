#pragma once

#include <string>
#include <memory>

#include "event/event.hpp"

class control
{
private:
	std::shared_ptr<event> handler;
	std::string url;

public:
	control(std::shared_ptr<event> handler, std::string url);
};