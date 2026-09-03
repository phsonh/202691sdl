#include "Frame.h"
#include <cstdint>
#include <SDL3/SDL.h>

namespace core::runtime::Frame {
	namespace {
		std::uint64_t FrameCount;
		std::uint64_t FrameStartTime;
		int TargetFPS;
		bool running;
	}
	
	void Init() {
		FrameCount = 0;
		FrameStartTime = 0;
		TargetFPS = 60;
		running = true;
	}
	void Begin() {
		FrameStartTime = SDL_GetTicksNS();
		FrameCount++;
	}
	void End() {
	}
	std::uint64_t GetFrameCount() {
		return FrameCount;
	}
	void Break() {
		running = false;
	}
	bool IsRunning() {
		return running;
	}
}