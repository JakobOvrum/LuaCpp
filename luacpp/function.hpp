#ifndef LCPP_FUNCTION_H
#define LCPP_FUNCTION_H

#include <tuple>
#include <luacpp/reference.hpp>
#include <luacpp/types.hpp>
#include <luacpp/stack.hpp>
#include <luacpp/lua.hpp>

namespace lua
{
    ///Lua function
    /**
        Object representing a Lua function.
    */
    class function : virtual public reference
    {
        public:
        ///Create empty reference to function
        /** \internal */
        function() : reference(){}

        ///Create reference to function on stack
        /**
            @param L stack containing function
            @param index position on stack
            \internal
        */
        function(lua_State* L, int index = -1) : reference(L, index)
        {
            assertType(L, index, type::function);
        }

        ///Call this function
        /**
            @param args arguments to pass to function
        */
        template<typename... Args>
        void operator()(Args&&... args)
        {
            push();
            pushArg(state(), args...);
            lua_call(state(), sizeof...(args), 0);
        }

        ///Call this function and get return value(s)
        /**
            @tparam Rets types of expected return values, in order

            @param args arguments to pass to function
            @return tuple of return values
        */
        // with return values
        template<typename... Rets, typename... Args>
        std::tuple<Rets...> call(Args&&... args)
        {
            push();
            pushArg(state(), args...);
            lua_call(state(), sizeof...(args), sizeof...(Rets));

            std::tuple<Rets...> ret;
            luaToTuple<sizeof...(Rets), Rets...>::fill(state(), ret);

            return ret;
        }

        private:
        template<typename T, typename... Args>
        void pushArg(lua_State* L, T&& arg, Args&&... args)
        {
            pushValue(L, arg);
            pushArg(L, args...);
        }

        void pushArg(lua_State* L){}
    };
}

#endif
