#ifndef LCPP_TABLE_H
#define LCPP_TABLE_H

#include <luacpp/reference.hpp>
#include <luacpp/lua.hpp>
#include <luacpp/stack.hpp>
#include <luacpp/types.hpp>

namespace lua
{
	class table : private reference
	{
		public:
		table() : reference(){}

		table(lua_State* L, int index = -1);

		void setMetaTable(table& meta);
		table getMetaTable();

		template<typename T, typename U>
		T get(U key) const
		{
			push();
			pushValue(state(), key);
			lua_gettable(state(), -2);

			assertType(state(), -1, typeOf<T>(state()));

			T t;
			getValue(state(), -1, t);

			lua_pop(state(), 2);
			return t;
		}

		template<typename T, typename U>
		void set(T key, U value)
		{
			push();
			pushValue(state(), key);
			pushValue(state(), value);
			lua_settable(state(), -3);
			lua_pop(state(), 1);
		}

		template<typename T>
		class index
		{
			public:
			index(table& t, T& k) : tab(t), key(k){}

			template<typename U>
			index<T>& operator=(U value)
			{
				tab.set(key, value);
				return *this;
			}

			template<typename U>
			operator U() const
			{
				return tab.get<U>(key);
			}

			private:
			table& tab;
			T& key;
		};

		template<typename T>
		index<T> operator[](T&& key)
		{
			return index<T>(*this, key);
		}

		template<typename T>
		const index<T> operator[](T&& key) const
		{
			return index<T>(const_cast<lua::table&>(*this), key);
		}
	};
}

#endif
