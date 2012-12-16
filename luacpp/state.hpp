#ifndef LCPP_STATE_H
#define LCPP_STATE_H

#include <luacpp/table.hpp>

struct lua_State;

namespace lua
{
    ///Lua state
    /**
        Object representing an instance of Lua.
    */
    class state
    {
        public:
        ///Create a new Lua state
        /**
            Keep in mind that this does not import the in-built libraries.
            @see openLibs()
        */
        state();

        ///Create a new wrapper for an existing state
        /**
            Wraps an existing lua_State. The underlying state will not be closed when this object is destroyed.
            This constructor is useful if your lua_State is not managed by your code.
            @param L lua_State object to wrap
        */
        state(lua_State* L);

        ///Import in-built libraries
        /**
            The in-built Lua standard library is not available until this function is called.
        */
        void openLibs();

        ///Run a string of Lua
        /**
            @param code Lua code to execute
            @throw lua::error thrown for syntax errors and uncaught runtime errors
        */
        void doString(const char* code);

        ///Run a Lua script
        /**
            @param path Path to script file to execute
            @throw lua::error thrown for syntax errors and uncaught runtime errors
        */
        void doFile(const char* path);

        ///Get global table
        /**
            @return Reference to the global environment
        */
        table& globals();

        ///Get registry table
        /**
            Note: do not put integer keys in this table, as they're reserved by the Lua reference mechanism which is used in LuaC++.
            @return Reference to the registry
        */
        table& registry();

        ///Get global table
        /**
            @return Immutable reference to the global environment
        */
        const table& globals() const;

        ///Get registry table
        /**
            @return Immutable reference to the registry
        */
        const table& registry() const;

        ///Create a new, empty table
        /**
            @param narr pre-allocate space for this number of array elements
            @param nrec pre-allocate space for this number of non-array elements
            @return empty table
        */
        table newTable(int narr = 0, int nrec = 0);

        ///Get global variable
        /**
            @tparam T variable type

            @param key variable key
            @return variable value
            See table::index for a list of possible types for T and U.

            @throw lua::error thrown if T or U are not convertible to Lua types (see table::index)
        */
        template<typename T, typename U>
        T get(U key) const
        {
            return _G.get<T>(key);
        }

        ///Set global variable
        /**
            @param key variable key
            @param value variable value
            See table::index for a list of possible types for T and U.

            @throw lua::error thrown if T or U are not convertible to Lua types (see table::index)
        */
        template<typename T, typename U>
        void set(T key, U value)
        {
            _G.set(key, value);
        }

        ///Use bracket syntax to get or set global variables
        /**
            @param key variable key
            @return assignable and convertible type
            @see table::index
        */
        template<typename T>
        table::index<T> operator[](T&& key) const
        {
            return _G[key];
        }

        private:
        void init();

        // lua_State* resource handle, to cleanly make it destruct last
        class handle
        {
            private:
            lua_State* L;
            bool owner;

            public:
            handle(lua_State* L, bool owner) : L(L), owner(owner) {}
            ~handle(){ if(owner) lua_close(L); }

            inline operator lua_State*(){ return L; }
        };
        table _G, _R;
        handle L;
    };
}

#endif
