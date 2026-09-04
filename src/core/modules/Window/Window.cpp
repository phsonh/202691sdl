#include "Window.h"
#include <string>
#include <SDL3/SDL.h>
#include "core/runtime/Log/Log.h"
#include <format>

namespace core::modules::Window {
    namespace {
        SDL_Window* window = nullptr;
    }
    bool Init(int width, int height) {
        if (window)
            return true;
        window = SDL_CreateWindow("",width,height,0);
        if (!window) {
            core::runtime::Log::Error(
                std::string("CreateWindow failed: ") +
                SDL_GetError()
            );
            return false;
        }
        core::runtime::Log::Debug(
            std::format(
                "Window module initialized: {}x{}",
                width,
                height
            )
        );

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
        core::runtime::Log::Debug(
            "Window module shutdown: window destroyed"
        );
    }
}

