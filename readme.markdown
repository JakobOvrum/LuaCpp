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
LuaC++ is a bridge between Lua and C++ which aims to remove the need to use the C API, including the Lua stack. It currently supports Lua version 5.1.

Requirements
------------------------------
LuaC++ makes use of the following C++0x features, which means your favorite compiler might not yet be able to compile and use LuaC++:

 * variadic templates
 * rvalue references
 * the <tuple> module

Additionally, when linking with Lua, make sure your Lua is compiled as C++ instead of C. This is because LuaC++ uses exceptions for error handling, which doesn't go very well with the default long jump behaviour.

License
==============================
LuaC++ is licensed under the terms of the MIT license, see the LICENSE file for more information.
