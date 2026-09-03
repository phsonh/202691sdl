#include "Lua.h"
#include <string>
#include <iostream>
#include "core/modules/Debug/Debug.h"

namespace core::runtime::Lua {
    namespace {
        lua_State* L = nullptr;
        int FrameFuncRef = LUA_NOREF;
    }
    bool Init() {
        if (L) {
            return true;
        }
        L = luaL_newstate();
        if (!L) {
            // std::cerr << "Lua state create failed\n";
            return false;
        }
            
        luaL_openlibs(L);
        return true;
	}
    lua_State* GetState() {
        return L;
    }

    bool DoFile(const std::string& path) {
        if (!L)
            return false;
        int result = luaL_dofile(L, path.c_str());
        if (result!=0) {
            const char* error = lua_tostring(L, -1);
            core::modules::Debug::ErrorBox(
                "Lua Error",
                error ? error : "Unknown Lua error"
            );
            lua_pop(L, 1);
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

        lua_pushvalue(L, index);

        FrameFuncRef =
            luaL_ref(
                L,
                LUA_REGISTRYINDEX
            );

        return true;
    }

    bool CallFrameFunc()
    {
        if (!L)
            return false;

        // 没有设置 FrameFunc，就当这一帧 Lua 什么都不做
        if (FrameFuncRef == LUA_NOREF)
            return true;

        // 从 Registry 把之前保存的函数压到栈顶
        lua_rawgeti(
            L,
            LUA_REGISTRYINDEX,
            FrameFuncRef
        );


        int result = lua_pcall(
            L,
            0,  // 参数数量
            0,  // 返回值数量
            0   // error handler
        );

        if (result != 0)
        {
            const char* error =
                lua_tostring(L, -1);

            core::modules::Debug::ErrorBox(
                "Lua Error",
                error ? error : "Unknown Lua error"
            );

            lua_pop(L, 1);

            return false;
        }

        return true;
    }

    void Shutdown() {
        if (!L)
            return;
        lua_close(L);
        L = nullptr;
    }
}