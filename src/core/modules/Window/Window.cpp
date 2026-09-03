#include "Window.h"
#include <iostream>
#include <SDL3/SDL.h>


namespace core::modules::Window {
    struct Engine_Window {
        SDL_Window* sdlWindow;
    };
    Engine_Window* Create(int width, int height) {
        // 先由sdl返回真正的窗口指针对象
        SDL_Window* window = SDL_CreateWindow("",width,height,0);
        if (!window) {
            std::cerr << "CreateWindow failed: " << SDL_GetError() << '\n';
            return nullptr;
        }
        // 只可意会不可言传
        Engine_Window* engineWindow = new Engine_Window;
        engineWindow->sdlWindow = window;        
        return engineWindow;
    }

    bool SetTitle(Engine_Window* window, const char* title) {
        if (!window)
            return false;
        return SDL_SetWindowTitle(window->sdlWindow, title);
    }

    bool SetSize(Engine_Window* window, int width, int height) {
        if (!window)
            return false;
        return SDL_SetWindowSize(window->sdlWindow,width,height);
    }

    void Destroy(Engine_Window*& window) {
        if (window) {
            SDL_DestroyWindow(window->sdlWindow);
            delete window;
            window = nullptr;
        }
    }
}

