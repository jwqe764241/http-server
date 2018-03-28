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