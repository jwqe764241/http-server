#pragma once

#include <string>

#include "file\path.hpp"

class content
{
private:
	std::string path;

public:
	content(std::string path);

	std::string get_content_type();

};