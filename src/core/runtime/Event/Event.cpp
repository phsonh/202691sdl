#include "Event.h"
#include <SDL3/SDL.h>


namespace core::runtime::Event {
    namespace {
        bool Initialized = false;
    }
    Engine_Events Events;
    bool Init() {
        if (Initialized) {
            return true;
        }
        Initialized = true;
        return true;
    }
    void Update() {
        Events = {};
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    Events.QuitRequested = true;
                    break;
                case SDL_EVENT_WINDOW_FOCUS_GAINED:
                    Events.FocusGained = true;
                    break;
                case SDL_EVENT_WINDOW_FOCUS_LOST:
                    Events.FocusLost = true;
                    break;
            }
        }
    }
    void Shutdown()
    {
        if (!Initialized) {
            return;
        }
        Initialized = false;
    }
}