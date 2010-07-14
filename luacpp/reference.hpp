#ifndef LCPP_REFERENCE_H
#define LCPP_REFERENCE_H

#include <luacpp/stack.hpp>
#include <luacpp/types.hpp>

struct lua_State;

namespace lua
{
	class reference
	{
		public:
		reference(lua_State* L, int index = -1);
		virtual ~reference();

		type::luatype type();
		const char* typeName();

		protected:
		reference();
		const reference& operator=(const reference& c);

		void push();
		inline lua_State* state(){ return L; }

		private:
		int copyRef() const;

		lua_State* L;
		int ref;

		friend void pushValue(lua_State* L, reference& ref);
	};
}

#endif
