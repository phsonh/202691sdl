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
            luaL_checktype(
                L,
                1,
                LUA_TSTRING
            );
            const char* title = lua_tostring(L, 1);
            bool success = core::modules::Window::SetTitle(title);
            if (!success) {

            }
            
            return 0;
        }
    } 

    void Register(lua_State* L) {
        // 全局变量modules
        lua_getglobal(L, "modules");
        if (lua_isnil(L, -1)) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_pushvalue(L, -1);
            lua_setglobal(L, "modules");
        }
        lua_newtable(L);
        lua_pushcfunction(L, SetTitle);
        lua_setfield(L, -2, "SetTitle");
        lua_setfield(L, -2, "Window");
        lua_pop(L, 1);
    }
}