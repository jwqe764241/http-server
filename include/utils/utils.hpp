#pragma once

#include <string>

#define _IMPLEMENT_SCOPE namespace server{
#define _IMPLEMENT_END }

using namespace std;

_IMPLEMENT_SCOPE

namespace global{

const string LINE_CHANGE("\n");

const string DIVIDE_BODY("\n\n");

const string HEADER_TOKEN(":");

const string WHITESPACE (" ");

}

_IMPLEMENT_END