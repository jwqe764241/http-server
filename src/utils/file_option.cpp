#include "utils/file_option.hpp"

file_option::file_option()
{
}

file_option::file_option(std::ifstream& file_stream)
try
{
	parse(file_stream);
}
catch(const std::exception& e)
{
	throw;
}

file_option::file_option(std::ifstream&& file_stream)
try
{
	parse(file_stream);
}
catch(const std::exception& e)
{
	throw;
}

file_option::~file_option()
{
}

void file_option::parse(std::ifstream& file_stream)
{
	if(file_stream.is_open())
	{
		std::string line;

		//Parse each line
		while(!file_stream.eof())
		{
			std::getline(file_stream, line);

			if(line.empty())
				continue;

			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

			int token_offset = line.find('=');
			if(token_offset != std::string::npos)
				container.insert(std::pair<std::string, std::string>(line.substr(0, token_offset), line.substr(token_offset + 1, line.size())));

		}
	}
	else
	{
		throw std::ifstream::failure("Can't access option file");
	}
}