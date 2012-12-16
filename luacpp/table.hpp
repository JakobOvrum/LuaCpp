#ifndef LCPP_TABLE_H
#define LCPP_TABLE_H

#include <luacpp/reference.hpp>
#include <luacpp/lua.hpp>
#include <luacpp/stack.hpp>
#include <luacpp/types.hpp>

namespace lua
{
    template<typename T>
    inline void checkType(lua_State* L, int index)
    {
        assertType(L, -1, typeOf<T>(L));
    }

    template<>
    inline void checkType<object>(lua_State* L, int index) {}

    ///Lua table
    /**
        Object representing a Lua table.
    */
    class table : virtual public reference
    {
        public:
        ///Create empty reference to table
        /** @internal */
        table() : reference(){}

        ///Create reference to table on stack
        /**
            @param L stack containing table
            @param index position on stack
            @internal
        */
        table(lua_State* L, int index = -1);

        ///Set this table's metatable
        /**
            @param meta new metatable
        */
        void setMetaTable(const table& meta);

        ///Get this table's metatable
        /**
            @return this table's metatable
            @throw lua::error thrown if this table's metatable is nil
        */
        table getMetaTable();

        ///Check for metatable
        /**
            @return boolean whether or not this table has a metatable
        */
        bool hasMetaTable();

        ///Look up variable in table
        /**
            @tparam T variable type

            @param key variable key
            @return variable value

            @throw lua::error thrown if T or U are not convertible to Lua types (see table::index)
        */
        template<typename T, typename U>
        T get(U key) const
        {
            push();
            pushValue(state(), key);
            lua_gettable(state(), -2);

            checkType<T>(state(), -1);

            T t;
            getValue(state(), -1, t);

            lua_pop(state(), 2);
            return t;
        }

        ///Set variable in table
        /**
            @param key variable key
            @param value variable value

            @throw lua::error thrown if T or U are not convertible to Lua types (see table::index)
        */
        template<typename T, typename U>
        void set(T key, U value)
        {
            push();
            pushValue(state(), key);
            pushValue(state(), value);
            lua_settable(state(), -3);
            lua_pop(state(), 1);
        }

        ///Assignable and convertible result of bracket-style lookup
        /**
            @tparam T type of key

            Returned by operator[] for lua::table and lua::state.
            Types supported for T and U:
            - number
                - lua_Integer (default 'int')
                - lua_Number (default 'double')

            - string
                - const char*
                - std::string

            - boolean
                - bool

            - table
                - lua::table

            - function
                - lua::function
                - any function R (*)(args...) where R is any
                convertible type, and args is a list of parameters
                of any convertible type. This is not supported whenever
                the type is returned to C++, only when pushing to Lua.

            - nil
                - lua::nil_t (use lua::nil)

            Note: this object is only assignable when non-const.
        */
        template<typename T>
        class index
        {
            public:
            ///Create new index association
            /**
                @param t table to operate on
                @param k key in table to operate on
                @internal
            */
            index(table& t, T& k) : tab(t), key(k){}

            ///Set t[k]
            /**
                @param value new value for t[k]

                @throw lua::error thrown if T or U are not convertible to Lua types (see table::index)
            */
            template<typename U>
            index<T>& operator=(U value)
            {
                tab.set(key, value);
                return *this;
            }

            ///Get t[k]
            /**
                @tparam U type to convert to

                @return value of t[k] as type U
                @throw lua::error thrown if T or U are not convertible to Lua types (see table::index)
            */
            template<typename U>
            operator U() const
            {
                return tab.get<U>(key);
            }

            private:
            table& tab;
            T& key;
        };

        ///Get or set variable in table with bracket-style syntax
        /**
            @param key variable key
            @return assignable and convertible handle for specified key in this table
            @see table::index
        */
        template<typename T>
        index<T> operator[](T&& key)
        {
            return index<T>(*this, key);
        }

        ///Get variable in table with bracket-style syntax
        /**
            @param key variable key
            @return convertible handle for specified key in this table
            @see table::index
        */
        template<typename T>
        const index<T> operator[](T&& key) const
        {
            return index<T>(const_cast<lua::table&>(*this), key);
        }
    };
}

#endif
