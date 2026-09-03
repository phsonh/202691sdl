#include "SDL.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace core::runtime::SDL {
	bool Init() {
        // 初始化
        bool sdl_init_success = SDL_Init(SDL_INIT_VIDEO);
        if (!sdl_init_success)
        {
            std::cerr << "SDL_Init failed: "
                << SDL_GetError() << '\n';
        }
		return sdl_init_success;
	}

    void Shutdown() {
        SDL_Quit();
    }
}