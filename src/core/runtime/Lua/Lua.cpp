#include "Lua.h"

namespace core::runtime::Lua {
	bool Init() {
        lua_State* L = luaL_newstate();
        return L

        /*
        luaL_openlibs(L);
        lua_close(L);
        */
	}
}