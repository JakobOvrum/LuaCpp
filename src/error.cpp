#include <luacpp/error.hpp>
#include <luacpp/lua.hpp>

namespace lua
{
    error::error(const char* what) : std::runtime_error(what)
    {
    }
}
