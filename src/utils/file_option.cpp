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
catch(std::exception& e)
{
	throw e;
}

file_option::file_option(std::ifstream&& file_stream)
try
{
	parse(file_stream);

	file_stream.close();
}
catch(std::exception& e)
{
	file_stream.close();

	throw e;
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

			std::cout << line << std::endl;
		}
	}
	else
	{
		throw server::parse_exception("can't access this stream");
	}
}
	
}
_IMPLEMENT_END