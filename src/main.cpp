#include <iostream>
#include <format>
#include <string>
#include "core/modules/Window/Window.h"
#include "core/runtime/Event/Event.h"
#include "core/runtime/Frame/Frame.h"
#include "core/runtime/Lua/Lua.h"
#include "core/runtime/SDL/SDL.h"
#include "lua_bind/modules/Window/Window.h"

int main(int argc, char* argv[])
{   
    // 初始化SDL
    if (!core::runtime::SDL::Init()) {
        return 1;
    }
    
    // 初始化窗口
    if (!core::modules::Window::Init(1280, 960)) {
        return 1;
    }
    // 初始化Lua
    if (!core::runtime::Lua::Init()) {
        return 1;
    }
    //初始化帧
    core::runtime::Frame::Init();
    lua_bind::modules::Window::Register(
        core::runtime::Lua::GetState()
    );
    core::runtime::Lua::DoFile("scripts/main.lua");
    //主循环
    while (core::runtime::Frame::IsRunning())
    {
        core::runtime::Frame::Begin();

        // 处理输入
        core::runtime::Event::Update();
        if (core::runtime::Event::Events.QuitRequested) {
            core::runtime::Frame::Break();
        }
        
        //std::string title = std::format("Frame: {} | FPS: {:.1f}",core::runtime::Frame::GetFrameCount(),core::runtime::Frame::GetCurrentFPS());
        //core::modules::Window::SetTitle(title.c_str());
        core::runtime::Frame::End();
    }
    core::runtime::Lua::Shutdown();
    core::modules::Window::Shutdown();
    core::runtime::SDL::Shutdown();
    
    return 0;
}