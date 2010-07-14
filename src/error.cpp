#include <luacpp/error.hpp>
#include <luacpp/lua.hpp>

namespace lua
{
	error::error(const char* what, int errcode) : std::runtime_error(what), err(errcode)
	{
	}

	int error::code()
	{
		return err;
	}
}
