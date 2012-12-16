#include <luacpp.hpp>

#include <cassert>

int main()
{
    lua::state lua;

    lua["foo"] = 1;
    assert(static_cast<int>(lua["foo"]) == 1);

    lua["foo"] = lua::nil;
    lua::object foo = lua["foo"];

    assert(foo == lua::nil);
}
