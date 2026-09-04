#include "Frame.h"
#include <cstdint>
#include <SDL3/SDL.h>
#include <format>
#include "core/runtime/Log/Log.h"

namespace core::runtime::Frame {
	namespace {
		bool Initialized = false;
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
	}
	bool Init()
	{
		if (Initialized)
			return true;

		FrameCount = 0;
		LastFrameTotalUsedTime = 0;
		TargetFPS = 60;
		FrameBudgetTime = NS_PER_SECOND / TargetFPS;
		ThisFrameStartTime = SDL_GetTicksNS();
		SDL_DelayPrecise( FrameBudgetTime );
		Initialized = true;
		core::runtime::Log::Debug(
			std::format(
				"Frame runtime initialized: target FPS = {}",
				TargetFPS
			)
		);

		return true;
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
	void Shutdown()
	{
		if (!Initialized)
			return;

		core::runtime::Log::Debug(
			std::format(
				"Frame runtime shutdown: total frames = {}",
				FrameCount
			)
		);

		Initialized = false;
	}
	std::uint64_t GetFrameCount() {
		return FrameCount;
	}
	void SetTargetFPS(int fps) {
		if (fps > 0) {
			TargetFPS = fps;
			FrameBudgetTime = NS_PER_SECOND / TargetFPS;
		}
			
	}
	double GetCurrentFPS() {
		return CurrentFPS;
	}
	int GetTargetFPS() {
		return TargetFPS;
	}
}