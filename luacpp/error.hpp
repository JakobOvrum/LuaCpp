#ifndef LCPP_ERROR_H
#define LCPP_ERROR_H

#include <stdexcept>

namespace lua
{
	class error : public std::runtime_error
	{
		public:
		error(const char* what, int errcode = 0);

		int code();

		private:
		int err;
	};
}

#endif
