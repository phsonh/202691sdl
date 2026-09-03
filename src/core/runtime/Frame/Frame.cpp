#include "Frame.h"
#include <cstdint>
#include <SDL3/SDL.h>

namespace core::runtime::Frame {
	namespace {
		constexpr std::uint64_t NS_PER_SECOND = 1'000'000'000;
		std::uint64_t FrameCount;
		std::uint64_t ThisFrameStartTime;
		std::uint64_t LastFrameStartTime;
		std::uint64_t LastFrameUsedTime;
		std::uint64_t FrameBudgetTime;
		int TargetFPS;
		double CurrentFPS;
		bool running;
	}
	void Init() {
		FrameCount = 0;
		ThisFrameStartTime = 0;
		LastFrameUsedTime = 0;
		TargetFPS = 60;
		running = true;
		FrameBudgetTime = NS_PER_SECOND / TargetFPS;
	}
	void Begin() {
		LastFrameStartTime = ThisFrameStartTime;
		ThisFrameStartTime = SDL_GetTicksNS();
		LastFrameUsedTime = ThisFrameStartTime - LastFrameStartTime;
		FrameCount++;
	}
	void End() {

		if ((SDL_GetTicksNS() - ThisFrameStartTime) < FrameBudgetTime) {
			SDL_DelayPrecise(FrameBudgetTime - (SDL_GetTicksNS() - ThisFrameStartTime));
		}
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
	void SetTargetFPS(int fps) {
		TargetFPS = fps;
	}
	double GetCurrentFPS() {
		return CurrentFPS;
	}
}