#include "Graphic.h"
#include "core/runtime/Log/Log.h"
#include "core/modules/Window/Window.h"
#include <SDL3/SDL.h>

namespace core::modules::Graphic {
	namespace {
		bool Initialized = false;
		SDL_Window* WindowHandle = nullptr;
	}
	bool Init() {
		if (Initialized)
			return true;

		WindowHandle = core::modules::Window::GetNativeHandle();
		if (!WindowHandle) {
			core::runtime::Log::Error("Graphic initialization failed: window is unavailable");
			return false;
		}
		Initialized = true;

		core::runtime::Log::Debug(
			"Graphic module initialized"
		);

		return true;
	}
	void Shutdown() {
		if (!Initialized)
			return;
		WindowHandle = nullptr;
		Initialized = false;

		core::runtime::Log::Debug(
			"Graphic module shutdown"
		);
	}
}