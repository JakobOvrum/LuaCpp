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
		state(lua_State* L);

		void openLibs();
		void doString(const char* code);
		void doFile(const char* path);
		table& globals();
		table& registry();

		const table& globals() const;
		const table& registry() const;

		table newTable(int narr = 0, int nrec = 0);

		template<typename T, typename U>
		T get(U key) const
		{
			return _G.get<T>(key);
		}

		template<typename T, typename U>
		void set(T key, U value)
		{
			_G.set(key, value);
		}

		template<typename T>
		table::index<T> operator[](T&& key) const
		{
			return _G[key];
		}

		private:
		void init();

		// lua_State* resource handle, to cleanly make it destruct last
		class handle
		{
			private:
			lua_State* L;
			bool owner;

			public:
			handle(lua_State* L, bool owner) : L(L), owner(owner) {}
			~handle(){ if(owner) lua_close(L); }

			inline operator lua_State*(){ return L; }
		};
		table _G, _R;
		handle L;
	};
}

#endif
