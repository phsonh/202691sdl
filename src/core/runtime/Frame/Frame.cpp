#include "Frame.h"
#include <cstdint>
#include <SDL3/SDL.h>

namespace core::runtime::Frame {
	namespace {
		constexpr std::uint64_t NS_PER_SECOND = 1'000'000'000;
		std::uint64_t FrameCount;
		std::uint64_t ThisFrameStartTime;
		std::uint64_t LastFrameStartTime;
		std::uint64_t LastFrameTotalUsedTime;
		std::uint64_t ThisFrameAlreadyUsedTime;
		std::int64_t ThisFrameTimeLeft;
		std::uint64_t FrameBudgetTime;
		int TargetFPS;
		double CurrentFPS;
		bool running;
	}
	void Init() {
		FrameCount = 0;
		LastFrameTotalUsedTime = 0;
		TargetFPS = 60;
		running = true;
		FrameBudgetTime = NS_PER_SECOND / TargetFPS;
		ThisFrameStartTime = SDL_GetTicksNS();
		SDL_DelayPrecise(FrameBudgetTime);
	}
	void Begin() {
		LastFrameStartTime = ThisFrameStartTime;
		ThisFrameStartTime = SDL_GetTicksNS();
		LastFrameTotalUsedTime = ThisFrameStartTime - LastFrameStartTime;
		FrameCount++;
		//计算上一帧的FPS
		CurrentFPS = static_cast<double>(NS_PER_SECOND) / static_cast<double>(LastFrameTotalUsedTime);
	}
	void End() {
		ThisFrameAlreadyUsedTime = SDL_GetTicksNS() - ThisFrameStartTime;
		ThisFrameTimeLeft = static_cast<std::int64_t>(FrameBudgetTime) - static_cast<std::int64_t>(ThisFrameAlreadyUsedTime);
		if (ThisFrameTimeLeft > 0) {
			SDL_DelayPrecise(ThisFrameTimeLeft);
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
		FrameBudgetTime = NS_PER_SECOND / TargetFPS;
	}
	double GetCurrentFPS() {
		return CurrentFPS;
	}
}