#include <iostream>
#include <string>
#include "core/modules/Window/Window.h"
#include "core/runtime/SDL/SDL.h"
#include "core/runtime/Frame/Frame.h"


int main(int argc, char* argv[])
{   
    // 初始化SDL
    if (!core::runtime::SDL::Init())
    {
        return 1;
    }
    //创建窗口
    core::modules::Window::Engine_Window* window = core::modules::Window::Create(1280, 960);
    //初始化帧
    core::runtime::Frame::Init();
    //主循环
    while (core::runtime::Frame::IsRunning())
    {
        core::runtime::Frame::Begin();

        // 处理输入
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                core::runtime::Frame::Break();
            }
        }
        core::modules::Window::SetTitle(window, std::to_string(FrameCount).c_str());

        core::runtime::Frame::End();
    }

    core::modules::Window::Destroy(window);
    core::runtime::SDL::Shutdown();
    return 0;
}