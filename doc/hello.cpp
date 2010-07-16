#include <luacpp.hpp>

int main()
{
    lua::state lua;
    lua.openLibs();

    lua::function print = lua["print"];
    print("Hello, world!");
}
