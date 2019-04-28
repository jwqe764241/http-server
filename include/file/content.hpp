#pragma once

#include <fstream>
#include <string>
#include <map>

#include "file\path.hpp"

static std::map<std::string, std::string> type_map =
{
	{"",	 "application/octet-stream"},
	{"css",  "text/css"},
	{"html", "text/html"},
	{"htm",  "text/html"},
	{"js",   "text/javascript"},
	{"txt",  "text/plain"},
	{"xml",  "text/xml"}
};

class content
{
private:
	std::string location;
	path elements;
public:
	content(std::string path);

	std::string get_path();
	std::string get_extension();
	std::ifstream get_stream();
	std::string get_type();

};