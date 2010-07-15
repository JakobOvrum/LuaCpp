#ifndef LCPP_FUNCTION_H
#define LCPP_FUNCTION_H

#include <tuple>
#include <luacpp/reference.hpp>
#include <luacpp/types.hpp>
#include <luacpp/stack.hpp>
#include <luacpp/lua.hpp>

namespace lua
{
	class function : virtual public reference
	{
		public:
		function() : reference(){}

		function(lua_State* L, int index = -1) : reference(L, index)
		{
			assertType(L, index, type::function);
		}

		template<typename... Args>
		void operator()(Args&&... args)
		{
			push();
			pushArg(state(), args...);
			lua_call(state(), sizeof...(args), 0);
		}

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
