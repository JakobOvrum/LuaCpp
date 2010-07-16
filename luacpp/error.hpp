#ifndef LCPP_ERROR_H
#define LCPP_ERROR_H

#include <stdexcept>

namespace lua
{
	///Lua error exception
	/**
		Thrown when an unhandled Lua error is raised (Lua panic).
	*/
	class error : public std::runtime_error
	{
		public:
		///Basic constructor
		/**
			@param what error message
			\internal
		*/
		error(const char* what);
	};
}

#endif
