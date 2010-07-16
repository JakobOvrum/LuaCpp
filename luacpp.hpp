#ifndef LCPP_LUACPP_H
#define LCPP_LUACPP_H

// doxygen index
/**
	@mainpage
	@section hello_sec Hello, world!
	@code
#include <luacpp.hpp>

int main()
{
	lua::state lua;
	lua.openLibs();

	lua::function print = lua["print"];
	print("Hello, world!");
}
	@endcode

	@section intro_sec Introduction

	LuaC++ is a bridge between Lua and C++ which aims to remove the need to use the C API,
	including the Lua stack. It currently supports Lua version 5.1.

	@section download_sec Download
	Full source code can be found at http://github.com/JakobOvrum/LuaCpp
*/

//doxygen examples
/**
	@example hello.cpp
	@example config.cpp
*/

#include "luacpp/error.hpp"
#include "luacpp/state.hpp"
#include "luacpp/table.hpp"
#include "luacpp/function.hpp"
#include "luacpp/object.hpp"
#include "luacpp/nil.hpp"

#endif
