#include "Window.h"
#include <lua.hpp>
#include "core/modules/Window/Window.h"


namespace lua_bind::modules::Window {
    namespace {
        int SetTitle(lua_State* L) {
            // 检测是否传了1个参数
            if (lua_gettop(L) != 1) {
                return luaL_error(
                    L,
                    "Window.SetTitle expects exactly 1 argument"
                );
            }
            //检测是否是字符串
            if (lua_type(L, 1) != LUA_TSTRING)
            {
                return luaL_error(
                    L,
                    "modules.Window.SetTitle: argument #1 must be a string"
                );
            }
            const char* title = lua_tostring(L, 1);
            if (!core::modules::Window::SetTitle(title))
            {
                return luaL_error(
                    L,
                    "modules.Window.SetTitle failed"
                );
            }
            
            return 0;
        }

        const luaL_Reg Functions[] =
        {
            { "SetTitle", SetTitle },
            // 结束标志
            { nullptr, nullptr }
        };
    } 

    void Register(lua_State* L) {
        luaL_register(
            L,
            "modules.Window",
            Functions
        );
        lua_pop(L, 1);
    }
}