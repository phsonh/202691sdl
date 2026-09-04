#include "Lua.h"

#include <string>

#include "core/runtime/Log/Log.h"

namespace core::runtime::Lua
{
    namespace
    {
        lua_State* L = nullptr;

        int FrameFuncRef = LUA_NOREF;


        void ReadAndPopError(
            std::string& error
        )
        {
            const char* message =
                lua_tostring(L, -1);

            error =
                message
                ? message
                : "Unknown Lua error";

            lua_pop(L, 1);
        }
    }


    bool Init()
    {
        if (L)
            return true;

        L = luaL_newstate();

        if (!L)
        {
            core::runtime::Log::Error(
                "Failed to create Lua state"
            );

            return false;
        }

        luaL_openlibs(L);

        core::runtime::Log::Debug(
            "Lua runtime initialized"
        );

        return true;
    }


    lua_State* GetState()
    {
        return L;
    }


    bool DoFile(
        const std::string& path,
        std::string& error
    )
    {
        error.clear();

        if (!L)
        {
            error =
                "Lua runtime is not initialized";

            return false;
        }

        int result =
            luaL_dofile(
                L,
                path.c_str()
            );

        if (result != 0)
        {
            ReadAndPopError(error);

            return false;
        }

        return true;
    }


    bool SetFrameFunc(int index)
    {
        if (!L)
            return false;

        if (!lua_isfunction(L, index))
            return false;

        if (FrameFuncRef != LUA_NOREF)
        {
            luaL_unref(
                L,
                LUA_REGISTRYINDEX,
                FrameFuncRef
            );
        }

        lua_pushvalue(
            L,
            index
        );

        FrameFuncRef =
            luaL_ref(
                L,
                LUA_REGISTRYINDEX
            );

        return true;
    }


    bool CallFrameFunc(
        std::string& error
    )
    {
        error.clear();

        if (!L)
        {
            error =
                "Lua runtime is not initialized";

            return false;
        }

        // Lua 没有设置 FrameFunc：
        // 这一帧什么都不执行，但不属于错误。
        if (FrameFuncRef == LUA_NOREF)
            return true;

        // Registry[FrameFuncRef]
        // → 压回 Lua stack
        lua_rawgeti(
            L,
            LUA_REGISTRYINDEX,
            FrameFuncRef
        );

        if (!lua_isfunction(L, -1))
        {
            lua_pop(L, 1);

            error =
                "Stored FrameFunc reference is not a function";

            return false;
        }

        int result =
            lua_pcall(
                L,
                0,
                0,
                0
            );

        if (result != 0)
        {
            ReadAndPopError(error);

            return false;
        }

        return true;
    }


    void Shutdown()
    {
        if (!L)
        {
            FrameFuncRef =
                LUA_NOREF;

            return;
        }

        if (FrameFuncRef != LUA_NOREF)
        {
            luaL_unref(
                L,
                LUA_REGISTRYINDEX,
                FrameFuncRef
            );

            FrameFuncRef =
                LUA_NOREF;
        }

        lua_close(L);

        L = nullptr;

        core::runtime::Log::Debug(
            "Lua runtime shutdown"
        );
    }
}