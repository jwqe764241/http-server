#pragma once

#include <string>

#define _IMPLEMENT_SCOPE namespace server{
#define _IMPLEMENT_END }

namespace character
{
	const std::string LINE_CHANGE("\n");
	const std::string DIVIDE_BODY("\n\n");
	const std::string HEADER_TOKEN(":");
	const std::string WHITESPACE (" ");
	const std::string PATH_DIVIDER("/");
	const std::string PARENT_DIRECTORY("..");
}

namespace utils
{
	namespace strings
	{
		template<typename t_pos, typename t_val>
		void delete_string(t_pos first, t_pos last, const t_val& find_value, t_val& source)
		{
			for(; first <= last; ++first) 
			{
				if(source[first] == *find_value.c_str())
					source.erase(first, 1);
			}
		}
	}

	const std::string HTTP_VERSION = "HTTP/1.1";
}