#include "Engine.h"
#include "core/modules/Window/Window.h"
#include "core/modules/Debug/Debug.h"
#include "core/runtime/Event/Event.h"
#include "core/runtime/Frame/Frame.h"
#include "core/modules/Math/Math.h"
#include "core/runtime/Lua/Lua.h"
#include "core/runtime/SDL/SDL.h"
#include "lua_bind/modules/Window/Window.h"
#include "lua_bind/modules/Frame/Frame.h"
#include "lua_bind/modules/Math/Math.h"

namespace engine {
    namespace {
        bool Runtime_Init() {
            return
                // 1
                core::runtime::SDL::Init() &&
                // 2
                core::runtime::Event::Init() &&
                // 3
                core::runtime::Frame::Init() &&
                // 4
                core::runtime::Lua::Init();
        }
        bool Modules_Init() {
            return
                // 1
                core::modules::Debug::Init() &&
                // 2
                core::modules::Window::Init(1280, 960) &&
                // 3
                core::modules::Math::Init();
        }
        bool LuaBind_Init()
        {
            lua_State* L =
                core::runtime::Lua::GetState();

            if (!L)
                return false;

            lua_bind::modules::Window::Register(L);
            lua_bind::modules::Frame::Register(L);
            lua_bind::modules::Math::Register(L);

            return core::runtime::Lua::DoFile(
                "scripts/main.lua"
            );
        }
        bool IsRunning = false;
        void Modules_Shutdown() {
            // 3
            core::modules::Math::Shutdown();
            // 2
            core::modules::Window::Shutdown();
            // 1
            core::modules::Debug::Shutdown();
        }
        void Runtime_Shutdown() {
            // 4
            core::runtime::Lua::Shutdown();
            // 3
            core::runtime::Frame::Shutdown();
            // 2
            core::runtime::Event::Shutdown();
            // 1
            core::runtime::SDL::Shutdown();
            
        }
    }
    bool Init()
    {
        IsRunning =
            Runtime_Init() &&
            Modules_Init() &&
            LuaBind_Init();
        return IsRunning;
    }
    bool Run() {
        while (IsRunning)
        {
            core::runtime::Frame::Begin();
            // 处理事件
            core::runtime::Event::Update();
            if (core::runtime::Event::Events.QuitRequested) {
                IsRunning = false;
            }
            if (!core::runtime::Lua::CallFrameFunc())
            {
                IsRunning = false;
                return false;
            }
            core::runtime::Frame::End();
        }
        return true;
    }
    void Shutdown() {
        IsRunning = false;
        // 卸载Modules
        Modules_Shutdown();
        // 关闭Runtime
        Runtime_Shutdown();
    }
}