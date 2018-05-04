#include "utils/option.hpp"

option::option()
{
}

option::option(const option& option)
{
}

option::option(const std::ofstream& file_stream)
{
}

option::option(const std::string& option_string)
{
}

option::~option()
{
}


void option::parse(const std::ofstream& file_stream)
{
}

void option::parse(const std::string& option_string)
{
}


void option::add(const std::pair<std::string, std::string>& element)
{
	container.insert(element);
}

int option::remove(const std::string& key)
{
	return container.erase(key);
}

std::string option::operator[](const std::string& key)
{
	return container[key];
}