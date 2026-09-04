#include <lua.hpp>
#include "Math.h"
#include "core/modules/Math/Math.h"

namespace lua_bind::modules::Math {
	namespace {
		int sin(lua_State* L) {
			if (lua_gettop(L) != 1) {
				return luaL_error(
					L,
					"modules.Math.sin expects exactly 1 argument"
				);
			}
			luaL_checktype(
				L,
				1,
				LUA_TNUMBER
			);
			double deg = static_cast<double>(lua_tonumber(L, 1));
			double result = core::modules::Math::sin(deg);
			lua_pushnumber(L,result);
			return 1;
		}
		int cos(lua_State* L) {
			if (lua_gettop(L) != 1) {
				return luaL_error(
					L,
					"modules.Math.cos expects exactly 1 argument"
				);
			}
			luaL_checktype(
				L,
				1,
				LUA_TNUMBER
			);
			double deg = static_cast<double>(lua_tonumber(L, 1));
			double result = core::modules::Math::cos(deg);
			lua_pushnumber(L, result);
			return 1;
		}
		int tan(lua_State* L) {
			if (lua_gettop(L) != 1) {
				return luaL_error(
					L,
					"modules.Math.tan expects exactly 1 argument"
				);
			}
			luaL_checktype(
				L,
				1,
				LUA_TNUMBER
			);
			double deg = static_cast<double>(lua_tonumber(L, 1));
			double result = core::modules::Math::tan(deg);
			lua_pushnumber(L, result);
			return 1;
		}
		int atan2(lua_State* L)
		{
			if (lua_gettop(L) != 2)
			{
				return luaL_error(
					L,
					"modules.Math.atan2 expects exactly 2 arguments"
				);
			}

			luaL_checktype(L, 1, LUA_TNUMBER);
			luaL_checktype(L, 2, LUA_TNUMBER);

			double dy =
				static_cast<double>(
					lua_tonumber(L, 1)
					);

			double dx =
				static_cast<double>(
					lua_tonumber(L, 2)
					);

			double result =
				core::modules::Math::atan2(
					dy,
					dx
				);

			lua_pushnumber(L, result);

			return 1;
		}
		int deg2rad(lua_State* L) {
			if (lua_gettop(L) != 1) {
				return luaL_error(
					L,
					"modules.Math.deg2rad expects exactly 1 argument"
				);
			}
			luaL_checktype(
				L,
				1,
				LUA_TNUMBER
			);
			double deg = static_cast<double>(lua_tonumber(L, 1));
			double result = core::modules::Math::deg2rad(deg);
			lua_pushnumber(L, result);
			return 1;
		}
		int rad2deg(lua_State* L) {
			if (lua_gettop(L) != 1) {
				return luaL_error(
					L,
					"modules.Math.rad2deg expects exactly 1 argument"
				);
			}
			luaL_checktype(
				L,
				1,
				LUA_TNUMBER
			);
			double rad = static_cast<double>(lua_tonumber(L, 1));
			double result = core::modules::Math::rad2deg(rad);
			lua_pushnumber(L, result);
			return 1;
		}

		const luaL_Reg Functions[] = {
			{ "sin", sin },
			{ "cos", cos },
			{ "tan", tan },
			{ "atan2", atan2 },
			{ "deg2rad", deg2rad },
			{ "rad2deg", rad2deg },
			{ nullptr, nullptr }
		};
	}
	void Register(lua_State* L) {
		luaL_register(
			L,
			"modules.Math",
			Functions
		);

		lua_pop(L, 1);
	}
}