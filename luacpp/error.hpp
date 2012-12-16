#ifndef LCPP_ERROR_H
#define LCPP_ERROR_H

#include <stdexcept>

namespace lua
{
    ///Lua error exception
    /**
        Thrown when an unhandled Lua error is raised.
        Keep in mind that the actual C++ exception is only thrown if Lua
        doesn't know what to do with one of its errors (Lua panic). This
        means that all cases of lua::error being thrown (as referenced in documentation)
        can, and will, be caught by protected Lua calls before being propagated as
        this exception.
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
