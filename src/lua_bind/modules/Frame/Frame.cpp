#include <lua.hpp>
#include "Frame.h"
#include "core/runtime/Lua/Lua.h"
#include "core/runtime/Frame/Frame.h"

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
			if (lua_gettop(L) != 1) {
				return luaL_error(
					L,
					"modules.Frame.SetTargetFPS expects exactly 1 argument"
				);
			}
			luaL_checktype(
				L,
				1,
				LUA_TNUMBER
			);

			int fps = static_cast<int>(
				lua_tointeger(L, 1)
			);

			if (fps <= 0)
			{
				return luaL_error(
					L,
					"modules.Frame.SetTargetFPS expects FPS greater than 0"
				);
			}
			core::runtime::Frame::SetTargetFPS(fps);
			return 0;
		}
		int GetCurrentFPS(lua_State* L) {
			if (lua_gettop(L) != 0)
			{
				return luaL_error(
					L,
					"modules.Frame.GetCurrentFPS expects no arguments"
				);
			}
			double fps = core::runtime::Frame::GetCurrentFPS();
			lua_pushnumber(L, fps);
			return 1;
		}
		int GetTargetFPS(lua_State* L) {
			if (lua_gettop(L) != 0)
			{
				return luaL_error(
					L,
					"modules.Frame.GetTargetFPS expects no arguments"
				);
			}
			double fps = core::runtime::Frame::GetTargetFPS();
			lua_pushnumber(L, fps);
			return 1;
		}
		int GetFrameCount(lua_State* L) {
			if (lua_gettop(L) != 0)
			{
				return luaL_error(
					L,
					"modules.Frame.GetFrameCount expects no arguments"
				);
			}
			double count = core::runtime::Frame::GetFrameCount();
			lua_pushnumber(L, count);
			return 1;
		}
		const luaL_Reg Functions[] = {
			{ "SetFrameFunc", SetFrameFunc },
			{ "SetTargetFPS", SetTargetFPS },
			{ "GetCurrentFPS", GetCurrentFPS },
			{ "GetTargetFPS", GetTargetFPS },
			{ "GetFrameCount", GetFrameCount },
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