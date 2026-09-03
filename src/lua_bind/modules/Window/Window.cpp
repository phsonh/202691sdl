#include "Window.h"
#include "core/modules/Window/Window.h"


namespace lua_bind::modules::Window {
    int SetTitle(lua_State* L, Engine_Window* window, const char* title) {

        core::modules::Window::SetTitle(window,title)
        return 0;
    }
}