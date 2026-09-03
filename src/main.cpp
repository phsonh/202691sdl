#include <iostream>
#include <format>
#include <string>
#include "core/modules/Window/Window.h"
#include "core/runtime/SDL/SDL.h"
#include "core/runtime/Frame/Frame.h"
#include "core/runtime/Event/Event.h"


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
        core::runtime::Event::Update();
        if (core::runtime::Event::Events.QuitRequested) {
            core::runtime::Frame::Break();
        }
        
        std::string title = std::format("Frame: {} | FPS: {:.1f}",core::runtime::Frame::GetFrameCount(),core::runtime::Frame::GetCurrentFPS());
        core::modules::Window::SetTitle(window,title.c_str());
        core::runtime::Frame::End();
    }
    core::modules::Window::Destroy(window);
    core::runtime::SDL::Shutdown();
    return 0;
}