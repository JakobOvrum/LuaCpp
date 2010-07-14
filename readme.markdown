Hello, world!
==============================
    #include <luacpp.hpp>

    int main()
    {
        lua::state lua;
        lua.openLibs();
        
        lua::function print = lua["print"];
        print("Hello, world!");
    }

LuaC++
==============================
LuaC++ is a bridge between Lua and C++ which aims to remove the need to use the C API, including the Lua stack.

Requirements
------------------------------
LuaC++ makes use of the following C++0x features, which means your favorite compiler might not yet be able to compile and use LuaC++:
 * variadic templates
 * rvalue references
 * the <tuple> module

License
==============================
LuaC++ is licensed under the terms of the MIT license, see the LICENSE file for more information.
