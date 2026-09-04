#pragma once

struct lua_State;

namespace lua_bind::modules::Debug
{
    void Register(lua_State* L);
}