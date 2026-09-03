#pragma once


namespace core::runtime::Event {
    struct Engine_Events
    {
        bool QuitRequested = false;
        bool FocusGained = false;
        bool FocusLost = false;
    };
    extern Engine_Events Events;
    void Update();
}