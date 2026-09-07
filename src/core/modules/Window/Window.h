#pragma once
#include <SDL3/SDL.h>

namespace core::modules::Window {
	bool Init(int width, int height);
	bool SetTitle(const char* title);
	SDL_Window* GetNativeHandle();
	void Shutdown();
}