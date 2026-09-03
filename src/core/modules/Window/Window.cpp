#include "Window.h"
#include <iostream>
#include <SDL3/SDL.h>


namespace core::modules::Window {
    namespace {
        SDL_Window* window = nullptr;
    }
    bool Init(int width, int height) {
        window = SDL_CreateWindow("",width,height,0);
        if (!window) {
            std::cerr << "CreateWindow failed: " << SDL_GetError() << '\n';
            return false;
        }
        return true;
    }
    bool SetTitle(const char* title) {
        return SDL_SetWindowTitle(window, title);
    }
    void Shutdown() {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

