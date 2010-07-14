#include <string>

#include <luacpp/stack.hpp>
#include <luacpp/reference.hpp>
#include <luacpp/table.hpp>
#include <luacpp/function.hpp>
#include <luacpp/lua.hpp>

namespace
{
	inline void assertArgType(lua_State* L, int narg, int type)
	{
		int t = lua_type(L, narg);
		if(t != type)
			luaL_typerror(L, narg, lua_typename(L, type));
	}
}

namespace lua
{
	// from Lua
	void getValue(lua_State* L, int index, table& r)
	{
		r = table(L, index);
	}

	void getArg(lua_State* L, int index, table& r)
	{
		assertArgType(L, index, LUA_TTABLE);
		getValue(L, index, r);
	}

	void getValue(lua_State* L, int index, function& r)
	{
		r = function(L, index);
	}

	void getArg(lua_State* L, int index, function& r)
	{
		assertArgType(L, index, LUA_TFUNCTION);
		getValue(L, index, r);
	}

	void getValue(lua_State* L, int index, lua_Integer& r)
	{
		r = lua_tointeger(L, index);
	}

	void getArg(lua_State* L, int index, lua_Integer& r)
	{
		assertArgType(L, index, LUA_TNUMBER);
		getValue(L, index, r);
	}

	void getValue(lua_State* L, int index, lua_Number& r)
	{
		r = lua_tonumber(L, index);
	}

	void getArg(lua_State* L, int index, lua_Number& r)
	{
		assertArgType(L, index, LUA_TNUMBER);
		getValue(L, index, r);
	}

	void getValue(lua_State* L, int index, bool& r)
	{
		r = lua_toboolean(L, index);
	}

	void getArg(lua_State* L, int index, bool& r)
	{
		assertArgType(L, index, LUA_TBOOLEAN);
		getValue(L, index, r);
	}

	void getValue(lua_State* L, int index, const char*& r)
	{
		r = lua_tostring(L, index);
	}

	void getArg(lua_State* L, int index, const char*& r)
	{
		assertArgType(L, index, LUA_TSTRING);
		getValue(L, index, r);
	}

	void getValue(lua_State* L, int index, const char*& r, size_t& len)
	{
		r = lua_tolstring(L, index, &len);
	}

	void getValue(lua_State* L, int index, std::string& r)
	{
		size_t len;
		const char* s = lua_tolstring(L, index, &len);
		r = std::string(s, len);
	}

	void getArg(lua_State* L, int index, std::string& r)
	{
		assertArgType(L, index, LUA_TSTRING);
		getValue(L, index, r);
	}

	// to Lua
	void pushValue(lua_State* L, reference& ref)
	{
		ref.push();
	}

	void pushValue(lua_State* L, lua_Integer i)
	{
		lua_pushinteger(L, i);
	}

	void pushValue(lua_State* L, lua_Number n)
	{
		lua_pushnumber(L, n);
	}

	void pushValue(lua_State* L, bool b)
	{
		lua_pushboolean(L, b);
	}

	void pushValue(lua_State* L, const char* s)
	{
		lua_pushstring(L, s);
	}

	void pushValue(lua_State* L, const char* s, size_t len)
	{
		lua_pushlstring(L, s, len);
	}

	void pushValue(lua_State* L, const std::string& str)
	{
		lua_pushlstring(L, str.c_str(), str.length());
	}

	void pushValue(lua_State* L, lua_CFunction f)
	{
		lua_pushcfunction(L, f);
	}
}
