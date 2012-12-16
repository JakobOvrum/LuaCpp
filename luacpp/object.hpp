#ifndef LCPP_OBJECT_H
#define LCPP_OBJECT_H

#include <luacpp/stack.hpp>
#include <luacpp/reference.hpp>
#include <luacpp/table.hpp>
#include <luacpp/function.hpp>

namespace lua
{
    class object : virtual public reference, public table, public function
    {
        public:
        object(lua_State* L, int index) : reference(L, index)
        {
        }

        object(){}

        template<typename T>
        operator T()
        {
            push();
            assertType(state(), -1, typeOf<T>(state()));

            T t;

            getValue(state(), -1, t);

            return t;
        }

        bool operator==(const reference& r);
        bool operator==(const nil_t& t);
    };
}

#endif
