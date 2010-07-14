#include <luacpp/reference.hpp>
#include <luacpp/lua.hpp>

namespace lua
{
	reference::reference(lua_State* L, int index) : L(L)
	{
		lua_pushvalue(L, index);
		ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	reference::~reference()
	{
		luaL_unref(L, LUA_REGISTRYINDEX, ref);
	}

	//for std::tuple compatibility
	reference::reference() : L(0), ref(LUA_NOREF) {}

	const reference& reference::operator=(const reference& c)
	{
		L = c.L, ref = c.copyRef();
		return *this;
	}

	void reference::push()
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
	}

	type::luatype reference::type()
	{
		push();
		int t = lua_type(L, -1);
		lua_pop(L, 1);
		return static_cast<type::luatype>(t);
	}

	const char* reference::typeName()
	{
		push();
		const char* s = luaL_typename(L, -1);
		lua_pop(L, 1);
		return s;
	}

	int reference::copyRef() const
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
		return luaL_ref(L, LUA_REGISTRYINDEX);
	}
}
