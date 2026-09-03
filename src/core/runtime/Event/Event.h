#pragma once


namespace core::runtime::Event {
    struct Engine_Events
    {
        bool QuitRequested = false;
        bool WindowResized = false;
        bool focusGained = false;
        bool focusLost = false;
        struct WindowSize {
            int width = 0;
            int height = 0;
        };
        WindowSize windowSize;
        
    };
    extern Engine_Events Events;
    void Update();
}