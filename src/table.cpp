#include <luacpp/table.hpp>
#include <luacpp/types.hpp>

namespace lua
{
    table::table(lua_State* L, int index) : reference(L, index)
    {
        assertType(L, index, type::table);
    }
}
