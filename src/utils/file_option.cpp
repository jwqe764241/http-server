#include "utils/file_option.hpp"

_IMPLEMENT_SCOPE
namespace option{

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
		throw parse_exception("Can't access option file", 0);
	}
}

}
_IMPLEMENT_END