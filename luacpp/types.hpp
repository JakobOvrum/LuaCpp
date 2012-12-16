#ifndef LCPP_TYPES_H
#define LCPP_TYPES_H

#include <luacpp/lua.hpp>
#include <luacpp/error.hpp>

#include <sstream>

namespace lua
{
    namespace type
    {
        enum luatype
        {
            none = LUA_TNONE,
            string = LUA_TSTRING,
            number = LUA_TNUMBER,
            thread = LUA_TTHREAD,
            boolean = LUA_TBOOLEAN,
            function = LUA_TFUNCTION,
            userdata = LUA_TUSERDATA,
            lightuserdata = LUA_TLIGHTUSERDATA,
            table = LUA_TTABLE
        };
    }

    inline void assertType(lua_State* L, int index, type::luatype expectedType)
    {
        int t = lua_type(L, index);
        if(t != expectedType)
            luaL_error(L, "expected %s, got %s", lua_typename(L, expectedType), lua_typename(L, t));
    }

    class table;
    class function;

    template<typename T>
    inline type::luatype typeOf(lua_State* L)
    {
        return type::none;
    }

    template<>
    inline type::luatype typeOf<table>(lua_State* L)
    {
        return type::table;
    }

    template<>
    inline type::luatype typeOf<function>(lua_State* L)
    {
        return type::function;
    }

    template<>
    inline type::luatype typeOf<lua_Number>(lua_State* L)
    {
        return type::number;
    }

    template<>
    inline type::luatype typeOf<lua_Integer>(lua_State* L)
    {
        return type::number;
    }

    template<>
    inline type::luatype typeOf<bool>(lua_State* L)
    {
        return type::boolean;
    }

    template<>
    inline type::luatype typeOf<const char*>(lua_State* L)
    {
        return type::string;
    }

    template<>
    inline type::luatype typeOf<std::string>(lua_State* L)
    {
        return type::string;
    }
}

#endif
