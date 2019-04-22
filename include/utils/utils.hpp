#pragma once

#include <string>

#define _IMPLEMENT_SCOPE namespace server{
#define _IMPLEMENT_END }

_IMPLEMENT_SCOPE

namespace global{

const std::string LINE_CHANGE("\n");

const std::string DIVIDE_BODY("\n\n");

const std::string HEADER_TOKEN(":");

const std::string WHITESPACE (" ");

const std::string PATH_DIVIDER("/");

}

_IMPLEMENT_END


namespace utils{

	namespace strings{
		template<class RangeCount, class T>
		void delete_string(RangeCount first, RangeCount last,
			const T& find_value, T& source)
		{
			for(; first <= last; ++first) 
			{
				if(source[first] == *find_value.c_str())
					source.erase(first, 1);
			}
		}
	}

}