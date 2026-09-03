#include "Event.h"
#include <SDL3/SDL.h>


namespace core::runtime::Event {
    Engine_Events Events;

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
}