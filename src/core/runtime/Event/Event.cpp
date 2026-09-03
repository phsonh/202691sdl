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
                case SDL_EVENT_WINDOW_RESIZED:
                    Events.WindowResized = true;
                    break;
                case SDL_EVENT_WINDOW_FOCUS_GAINED:
                    Events.focusGained = true;
                    break;
                case SDL_EVENT_WINDOW_FOCUS_LOST:
                    Events.focusLost = true;
                    break;
            }
        }
        
    }
}