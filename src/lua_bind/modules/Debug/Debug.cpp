#include <lua.hpp>

#include "Debug.h"
#include "core/runtime/Log/Log.h"

namespace lua_bind::modules::Debug
{
    namespace
    {
        int Log(lua_State* L)
        {
            if (lua_gettop(L) != 1)
            {
                return luaL_error(
                    L,
                    "modules.Debug.Log expects exactly 1 argument"
                );
            }

            luaL_checktype(
                L,
                1,
                LUA_TSTRING
            );

            const char* message =
                lua_tostring(L, 1);

            core::runtime::Log::Info(
                message
            );

            return 0;
        }


        int Warn(lua_State* L)
        {
            if (lua_gettop(L) != 1)
            {
                return luaL_error(
                    L,
                    "modules.Debug.Warn expects exactly 1 argument"
                );
            }

            luaL_checktype(
                L,
                1,
                LUA_TSTRING
            );

            const char* message =
                lua_tostring(L, 1);

            core::runtime::Log::Warn(
                message
            );

            return 0;
        }


        int Error(lua_State* L)
        {
            if (lua_gettop(L) != 1)
            {
                return luaL_error(
                    L,
                    "modules.Debug.Error expects exactly 1 argument"
                );
            }

            luaL_checktype(
                L,
                1,
                LUA_TSTRING
            );

            const char* message =
                lua_tostring(L, 1);

            return luaL_error(
                L,
                "%s",
                message
            );
        }


        const luaL_Reg Functions[] = {
            { "Log",   Log   },
            { "Warn",  Warn  },
            { "Error", Error },
            { nullptr, nullptr }
        };
    }


    void Register(lua_State* L)
    {
        luaL_register(
            L,
            "modules.Debug",
            Functions
        );

        lua_pop(L, 1);
    }
}