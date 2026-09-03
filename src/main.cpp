#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>
#include <lua.hpp>
#include "core/modules/Window/Window.h"
#include "core/runtime/SDL/SDL.h"
#include "core/runtime/Frame/Frame.h"


int main(int argc, char* argv[])
{   
    lua_State* L = luaL_newstate();

    if (!L)
    {
        return 1;
    }

    luaL_openlibs(L);
    lua_close(L);


    // 初始化
    if (!core::runtime::SDL::Init())
    {
        return 1;
    }
    //创建窗口
    core::modules::Window::Engine_Window* window = core::modules::Window::Create(1280, 960);
    //
    core::runtime::Frame::Init()
    while (core::runtime::Frame::IsRunning())
    {

        // 处理输入
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
        // 帧计数
        FrameCount++;
        core::modules::Window::SetTitle(window, std::to_string(FrameCount).c_str());
    }

    core::modules::Window::Destroy(window);
    core::runtime::SDL::Shutdown();

    return 0;
}