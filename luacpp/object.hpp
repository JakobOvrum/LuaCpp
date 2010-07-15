#ifndef LCPP_OBJECT_H
#define LCPP_OBJECT_H

#include <luacpp/reference.hpp>
#include <luacpp/table.hpp>
#include <luacpp/function.hpp>

namespace lua
{
	class object : virtual public reference, public table, public function
	{
		public:
		object(lua_State* L, int index) : reference(L, index)
		{
		}

		object(){}

		private:
	};
}

#endif
