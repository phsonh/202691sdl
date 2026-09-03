#include <lua.hpp>
#include "Frame.h"
#include "core/runtime/Lua/Lua.h"

namespace lua_bind::modules::Frame {
	namespace {
		int SetFrameFunc(lua_State* L) {
			if (lua_gettop(L) != 1) {
				return luaL_error(
					L,
					"modules.Frame.SetFrameFunc expects exactly 1 argument"
				);
			}

			luaL_checktype(
				L,
				1,
				LUA_TFUNCTION
			);

			if (!core::runtime::Lua::SetFrameFunc(1))
			{
				return luaL_error(
					L,
					"modules.Frame.SetFrameFunc failed"
				);
			}

			return 0;
		}
		int SetTargetFPS(lua_State* L) {
			return 0;
		}
		const luaL_Reg Functions[] = {
			{ "SetFrameFunc", SetFrameFunc },
			{ nullptr, nullptr }
		};
	}
	void Register(lua_State* L) {
		luaL_register(
			L,
			"modules.Frame",
			Functions
		);

		lua_pop(L, 1);
	}
}