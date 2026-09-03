#pragma once
#include <lua.hpp>
#include <string>


namespace core::runtime::Lua {
	bool Init();
	lua_State* GetState();
	bool DoFile(const std::string& path);
	void Shutdown();
}