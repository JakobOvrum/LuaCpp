#include <luacpp.hpp>

double mul(double a, double b)
{
    return a * b;
}

std::string quotify(std::string a)
{
    return '"' + a + '"';
}

const char* getTestField(lua::table t)
{
    return t["test"];
}

int main()
{
    lua::state lua;
    lua.openLibs();

    lua["mul"] = mul;
    lua.doString("assert(mul(3, 2) == 3 * 2)");

    lua["quotify"] = quotify;
    lua.doString("assert(quotify('foo') == '\"foo\"')");

    lua["getTestField"] = getTestField;
    lua.doString("assert(getTestField{test = 'foo'} == 'foo')");
}
