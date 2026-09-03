#include "Window.h"
#include <iostream>
#include <SDL3/SDL.h>


namespace core::modules::Window {
    namespace {
        SDL_Window* window = nullptr;
    }
    bool Init(int width, int height) {
        if (window)
            return true;
        window = SDL_CreateWindow("",width,height,0);
        if (!window) {
            std::cerr << "CreateWindow failed: " << SDL_GetError() << '\n';
            return false;
        }
        return true;
    }
    bool SetTitle(const char* title) {
        if (!window) {
            return false;
        }
        return SDL_SetWindowTitle(window, title);
    }
    void Shutdown() {
        if (!window) {
            return;
        }
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

