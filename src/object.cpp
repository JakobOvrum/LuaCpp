#include <luacpp/object.hpp>
#include <luacpp/lua.hpp>

namespace lua
{
    bool object::operator==(const reference& r)
    {
        push();
        r.push();
        bool b = lua_equal(state(), -1, -2);
        lua_pop(state(), 2);
        return b;
    }

    bool object::operator==(const nil_t& n)
    {
        push();
        bool b = lua_isnil(state(), -1);
        lua_pop(state(), 1);
        return b;
    }
}
