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
Check out the example/ and test/ subdirectories for usage examples.

Documentation
------------------------------
Documentation can be browsed online [here](http://jakobovrum.github.com/LuaCpp/index.html), or checked out at the gh-pages branch.

Alternatively, run `doxygen Doxyfile` from the project root directory to generate documentation from source (you might want to change the OUTPUT_DIRECTORY configuration value found in Doxyfile).

Requirements
------------------------------
LuaC++ makes use of the following C++0x features, which means your favorite compiler might not yet be able to compile and use LuaC++:

 * variadic templates
 * rvalue references
 * the tuple module

Additionally, as LuaC++ uses C++ exceptions for error handling, make sure your Lua library is compiled as C++.

License
==============================
LuaC++ is licensed under the terms of the MIT license, see the LICENSE file for more information.
