#ifndef LCPP_STATE_H
#define LCPP_STATE_H

#include <luacpp/table.hpp>

struct lua_State;

namespace lua
{
	class state
	{
		public:
		state();
		virtual ~state();

		void openLibs();
		void doString(const char* code);
		void doFile(const char* path);
		table& globals();
		table& registry();

		table newTable(int narr = 0, int nrec = 0);

		template<typename T, typename U>
		T get(U key)
		{
			return _G.get<T>(key);
		}

		template<typename T, typename U>
		void set(T key, U value)
		{
			_G.set(key, value);
		}

		template<typename T>
		table::index<T> operator[](T&& key)
		{
			return _G[key];
		}

		private:
		lua_State* L;
		table _G, _R;
	};
}

#endif
