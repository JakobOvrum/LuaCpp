#include <luacpp.hpp>

#include <cstring>
#include <cassert>

int main()
{
	lua::state lua;
	lua.openLibs();

	lua["foo"] = "bar";

	try
	{
		int i = lua["foo"];
		lua::function print = lua["print"];
		print(i);
	}
	catch(lua::error& err)
	{
		assert(std::strcmp(err.what(), "expected number, got string") == 0);
	}
}

