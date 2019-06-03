#pragma once

#include <string>

#define _IMPLEMENT_SCOPE namespace web{
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
		template<typename RangeCount, typename T>
		void delete_string(RangeCount first, RangeCount last, const T& find_value, T& source)
		{
			for(; first <= last; ++first) 
			{
				if(source[first] == *find_value.c_str())
					source.erase(first, 1);
			}
		}
	}
}