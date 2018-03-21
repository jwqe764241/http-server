#pragma once

#include <string>

#define _IMPLEMENT_SCOPE namespace server{
#define _IMPLEMENT_END }

_IMPLEMENT_SCOPE

namespace global{

extern
const std::string LINE_CHANGE("\r\n");

}

_IMPLEMENT_END