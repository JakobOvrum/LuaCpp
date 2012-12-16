#ifndef LCPP_NIL_H
#define LCPP_NIL_H

namespace lua
{
    ///Unique type representing Lua nil
    /**
        Use the constant lua::nil.
    */
    struct nil_t
    {
    };

    ///Object instance representing Lua nil
    /**
        Useful for clearing keys in tables.
        @see table::index
    */
    extern nil_t nil;
}

#endif
