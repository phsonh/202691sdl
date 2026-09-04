#pragma once
#include <lua.hpp>
#include <string>

namespace core::runtime::Lua
{
    bool Init();

    lua_State* GetState();

    bool DoFile(
        const std::string& path,
        std::string& error
    );

    bool SetFrameFunc(int index);

    bool CallFrameFunc(
        std::string& error
    );

    void Shutdown();
}