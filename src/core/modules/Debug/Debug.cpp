// Debug.cpp
#include "Debug.h"
#include <SDL3/SDL.h>
#include "core/runtime/Log/Log.h"

namespace core::modules::Debug
{   
    namespace {
        bool Initialized = false;
    }
    bool Init()
    {
        if (Initialized)
            return true;

        Initialized = true;

        core::runtime::Log::Debug(
            "Debug module initialized"
        );

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
    void Shutdown()
    {
        if (!Initialized)
            return;

        Initialized = false;

        core::runtime::Log::Debug(
            "Debug module shutdown"
        );
    }
}