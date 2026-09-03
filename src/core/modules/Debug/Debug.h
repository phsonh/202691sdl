#pragma once


namespace core::modules::Debug
{   
    bool Init();
    void ErrorBox(
        const char* title,
        const char* message
    );
    void Shutdown();
}