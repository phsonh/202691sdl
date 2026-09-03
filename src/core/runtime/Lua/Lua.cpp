#include "Lua.h"
#include <string>


namespace core::runtime::Lua {
    namespace {
        lua_State* L = nullptr;
    }
    bool Init() {
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