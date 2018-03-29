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

}

_IMPLEMENT_END


namespace utils{

	namespace strings{
		template<class RangeCount, class T>
		void delete_string(RangeCount first, RangeCount last,
			const T& old_value, const T& new_value, T& source)
		{
			for(; first != last; ++first) {
				if(source[first] == *old_value.c_str()) {
					source.erase(first, 1);
					first -= 1;
				}
			}
		}
	}

}