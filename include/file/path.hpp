#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "part.hpp"
#include "utils/utils.hpp"

class path
{
private:
	std::vector<part> parts;

public:
	path();
	path(std::string path_string);
	~path();
	
	void append(const std::string& path_string);
	void append(const path& path);
	void append(const part& part);

	size_t get_size();
	part get_part(int index);
	part get_first_part();
	part get_last_part();
	std::string get_path_string();
	const std::vector<part> get_part_container();

	void operator+=(const std::string& lhs);
	void operator+=(const path& lhs);
};