#include <luacpp/state.hpp>
#include <luacpp/error.hpp>

#include <luacpp/lua.hpp>

namespace
{
	int atpanic(lua_State* L)
	{
		throw lua::error(lua_tostring(L, -1));
	}
}

namespace lua
{
	state::state() : L(luaL_newstate()), _G(L, LUA_GLOBALSINDEX), _R(L, LUA_REGISTRYINDEX)
	{
		lua_atpanic(L, atpanic);
	}

	state::~state()
	{
		lua_close(L);
	}

	void state::openLibs()
	{
		luaL_openlibs(L);
	}

	void state::doString(const char* code)
	{
		int err = luaL_dostring(L, code);
		if(err)
			lua_error(L);
	}

	void state::doFile(const char* path)
	{
		int err = luaL_dofile(L, path);
		if(err)
			lua_error(L);
	}

	table& state::globals()
	{
		return _G;
	}

	const table& state::globals() const
	{
		return _G;
	}

	table& state::registry()
	{
		return _R;
	}

	const table& state::registry() const
	{
		return _R;
	}

	table state::newTable(int narr, int nrec)
	{
		lua_createtable(L, narr, nrec);
		table t(L);
		lua_pop(L, 1);
		return t;
	}
}
