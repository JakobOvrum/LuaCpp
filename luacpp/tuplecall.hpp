#ifndef LCPP_TUPLECALL_H
#define LCPP_TUPLECALL_H

#include <tuple>

//Author: doublep from #c++ on FreeNode IRC, thanks

namespace tuplecall
{
	template<typename Return, typename Func, typename Tuple, std::size_t need_indices, std::size_t... index>
	struct dispatcher : public dispatcher<Return, Func, Tuple, need_indices - 1, need_indices - 1, index...> {};

	template<typename Return, typename Func, typename Tuple, std::size_t... index>
	struct dispatcher<Return, Func, Tuple, 0, index...>
	{
		static Return call(Func func, const Tuple& args)
		{
	  		return func(std::get <index> (args)...);
		}
	};

	template <typename Return, typename... Args>
	Return call(Return (* func) (Args...), const std::tuple <Args...>& args)
	{
		return dispatcher <Return, Return (*) (Args...), std::tuple <Args...>, sizeof...(Args)>::call(func, args);
	}
}

#endif
