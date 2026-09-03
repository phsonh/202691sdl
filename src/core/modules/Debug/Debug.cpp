// Debug.cpp
#include "Debug.h"
#include <SDL3/SDL.h>

namespace core::modules::Debug
{   
    namespace {
        bool Initialized = false;
    }
    bool Init() {
        if (Initialized) {
            return true;
        }
        Initialized = true;
        return true;
    }
    void ErrorBox(
        const char* title,
        const char* message
    )
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            title,
            message,
            nullptr
        );
    }
    void Shutdown() {
        if (!Initialized) {
            return;
        }
        Initialized = false;
    }
}