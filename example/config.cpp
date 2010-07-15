#include <luacpp.hpp>

#include <iostream>

struct Config
{
	int foo;
	const char* bar;
};

Config loadConfig(const lua::table& t)
{
	Config c;
	c.foo = t["foo"];
	c.bar = t["bar"];
	return c;
}

int main()
{
	lua::state configState;
	Config config;
	try
	{
		configState.doFile("example/config.lua");
		config = loadConfig(configState.globals());
	}
	catch(lua::error& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}

	std::cout << "foo: " << config.foo << std::endl;
	std::cout << "bar: " << config.bar << std::endl;
}
