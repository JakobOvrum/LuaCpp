#include <luacpp.hpp>

#include <tuple>

#include <cassert>
#include <cstring>

int main()
{
	lua::state lua;
	lua.doString("function test() return 42, 'hello' end");

	lua::function test = lua["test"];

	auto ret = test.call<int, const char*>(); // returns std::tuple<int, const char*>

	assert(std::get<0>(ret) == 42);
	assert(std::strcmp(std::get<1>(ret), "hello") == 0);
}
