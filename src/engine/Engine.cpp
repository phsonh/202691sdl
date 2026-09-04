#include "Engine.h"
#include <string>
#include "core/runtime/Log/Log.h"
#include "core/runtime/Event/Event.h"
#include "core/runtime/Frame/Frame.h"
#include "core/runtime/Lua/Lua.h"
#include "core/runtime/SDL/SDL.h"
#include "core/modules/Window/Window.h"
#include "core/modules/Debug/Debug.h"
#include "core/modules/Math/Math.h"
#include "lua_bind/modules/Window/Window.h"
#include "lua_bind/modules/Frame/Frame.h"
#include "lua_bind/modules/Math/Math.h"
#include "lua_bind/modules/Debug/Debug.h"

namespace engine {
    namespace {
        bool IsRunning = false;
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
        void ReportLuaError(
            const char* context,
            const std::string& error
        )
        {
            std::string message =
                std::string(context) +
                ": " +
                error;

            core::runtime::Log::Error(
                message
            );

            core::modules::Debug::ErrorBox(
                "Lua Error",
                message.c_str()
            );
        }
        bool LuaBind_Init()
        {
            lua_State* L =
                core::runtime::Lua::GetState();

            if (!L)
            {
                core::runtime::Log::Error(
                    "Lua state is unavailable during Lua binding initialization"
                );

                return false;
            }

            lua_bind::modules::Window::Register(L);
            lua_bind::modules::Frame::Register(L);
            lua_bind::modules::Math::Register(L);
            lua_bind::modules::Debug::Register(L);


            std::string luaError;

            if (!core::runtime::Lua::DoFile(
                "scripts/main.lua",
                luaError
            ))
            {
                ReportLuaError(
                    "Failed to execute scripts/main.lua",
                    luaError
                );

                return false;
            }

            return true;
        }
        
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
        if (!core::runtime::Log::Init())
            return false;

        core::runtime::Log::Info(
            "Engine initializing"
        );

        IsRunning =
            Runtime_Init() &&
            Modules_Init() &&
            LuaBind_Init();

        if (!IsRunning)
        {
            core::runtime::Log::Fatal(
                "Engine initialization failed"
            );

            return false;
        }

        core::runtime::Log::Info(
            "Engine initialized"
        );

        return true;
    }
    bool Run()
    {
        std::string luaError;

        while (IsRunning)
        {
            core::runtime::Frame::Begin();

            // 处理事件
            core::runtime::Event::Update();

            if (
                core::runtime::Event::Events.QuitRequested
                )
            {
                IsRunning = false;
            }


            if (!core::runtime::Lua::CallFrameFunc(
                luaError
            ))
            {
                ReportLuaError(
                    "Lua frame callback failed",
                    luaError
                );

                IsRunning = false;

                return false;
            }


            core::runtime::Frame::End();
        }

        return true;
    }
    void Shutdown()
    {
        IsRunning = false;

        core::runtime::Log::Info(
            "Engine shutting down"
        );

        // 卸载 Modules
        Modules_Shutdown();

        // 关闭 Runtime
        Runtime_Shutdown();

        core::runtime::Log::Info(
            "Engine shutdown complete"
        );

        // Log 永远最后关闭
        core::runtime::Log::Shutdown();
    }
}