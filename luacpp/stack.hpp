#ifndef LCPP_STACK_H
#define LCPP_STACK_H

#include <tuple>
#include <string>

#include <luacpp/reference.hpp>
#include <luacpp/types.hpp>
#include <luacpp/lua.hpp>

#include <luacpp/tuplecall.hpp>

namespace lua
{
    class table;
    class function;
    class object;
    class nil_t;

    // from Lua
    void getValue(lua_State* L, int index, table& r);
    void getValue(lua_State* L, int index, function& r);
    void getValue(lua_State* L, int index, object& r);
    void getValue(lua_State* L, int index, lua_Integer& r);
    void getValue(lua_State* L, int index, lua_Number& r);
    void getValue(lua_State* L, int index, bool& r);
    void getValue(lua_State* L, int index, const char*& r);
    void getValue(lua_State* L, int index, const char*& r, size_t& len);
    void getValue(lua_State* L, int index, std::string& r);

    template<typename T>
    inline void getArg(lua_State* L, int narg, T& r)
    {
        int type = typeOf<T>(L);
        int t = lua_type(L, narg);
        if(t != type)
            luaL_typerror(L, narg, lua_typename(L, type));

        getValue(L, narg, r);
    }

    inline void getArg(lua_State* L, int narg, object& r)
    {
        getValue(L, narg, r);
    }

    // to Lua
    class reference;

    void pushValue(lua_State* L, reference& ref);
    void pushValue(lua_State* L, lua_Integer i);
    void pushValue(lua_State* L, lua_Number n);
    void pushValue(lua_State* L, bool b);
    void pushValue(lua_State* L, const char* s);
    void pushValue(lua_State* L, const char* s, size_t len);
    void pushValue(lua_State* L, const std::string& str);
    void pushValue(lua_State* L, lua_CFunction f);
    void pushValue(lua_State* L, nil_t& n);

    template<int n, typename... Args>
    struct luaToTuple
    {
        static void fill(lua_State* L, std::tuple<Args...>& args)
        {
            getArg(L, sizeof...(Args) - n + 1, std::get<sizeof...(Args) - n>(args));
            luaToTuple<n - 1, Args...>::fill(L, args);
        }
    };

    template<typename... Args>
    struct luaToTuple<0, Args...>
    {
        static void fill(lua_State* L, std::tuple<Args...>& args) {}
    };

    // regular single return value
    template<typename R, typename... Args>
    struct tupleCaller
    {
        static int call(lua_State* L, R (*f)(Args...), std::tuple<Args...>& args)
        {
            R r = tuplecall::call(f, args);
            pushValue(L, r);
            return 1;
        }
    };

    // no return value
    template<typename... Args>
    struct tupleCaller<void, Args...>
    {
        static int call(lua_State* L, void (*f)(Args...), std::tuple<Args...>& args)
        {
            tuplecall::call(f, args);
            return 0;
        }
    };

    template<typename R, typename... Args>
    int functionWrapper(lua_State* L)
    {
        size_t top = lua_gettop(L);
        if(top < sizeof...(Args))
            luaL_error(L, "expected %d arguments, got %d", sizeof...(Args), top);

        typedef R (*T)(Args...);
        T f = (T)(lua_touserdata(L, lua_upvalueindex(1)));

        std::tuple<Args...> args;
        luaToTuple<sizeof...(Args), Args...>::fill(L, args);

        return tupleCaller<R, Args...>::call(L, f, args);
    }

    template<typename R, typename... Args>
    void pushValue(lua_State* L, R (*f)(Args...))
    {
        lua_pushlightuserdata(L, (void*)f);
        lua_pushcclosure(L, functionWrapper<R, Args...>, 1);
    }
}

#endif
