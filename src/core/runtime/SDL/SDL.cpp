#include "SDL.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace core::runtime::SDL {
    namespace {
        bool Initialized = false;
    }
	bool Init() {
        // 初始化
        if (Initialized) {
            return true;
        }
        bool sdl_init_success = SDL_Init(SDL_INIT_VIDEO);
        if (!sdl_init_success)
        {
            std::cerr << "SDL_Init failed: "
                << SDL_GetError() << '\n';
            return false;
        }
        Initialized = true;
        return true;
	}

    void Shutdown() {
        if (!Initialized) {
            return;
        }
        SDL_Quit();
        Initialized = false;
    }
}