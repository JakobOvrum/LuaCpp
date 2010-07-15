#ifndef LCPP_REFERENCE_H
#define LCPP_REFERENCE_H

#include <luacpp/stack.hpp>
#include <luacpp/types.hpp>

struct lua_State;

namespace lua
{
	class object;

	class reference
	{
		public:
		reference(lua_State* L, int index = -1);
		reference(const reference& c);
		virtual ~reference();

		type::luatype type() const;
		const char* typeName() const;

		protected:
		reference();
		const reference& operator=(const reference& c);

		void push() const;
		inline lua_State* state() const
		{
			return L;
		}

		private:
		int copyRef() const;

		lua_State* L;
		int ref;

		friend void pushValue(lua_State* L, reference& ref);
		friend class object;
	};
}

#endif
