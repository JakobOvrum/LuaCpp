#include <luacpp.hpp>

#include <tuple>

int main()
{
	lua::state lua;
	lua.openLibs();

	lua.doString("function test() return 42, 'hello' end");
	lua::function test = lua["test"];

	auto ret = test.call<int, const char*>(); //returns std::tuple<int, const char*>

	lua::function print = lua["print"];
	print(std::get<0>(ret), std::get<1>(ret));
}
