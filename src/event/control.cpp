#include "event/control.hpp"

control::control(std::shared_ptr<event> handler, std::string url)
	: handler(handler), url(url)
{

}