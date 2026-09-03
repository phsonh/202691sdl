#pragma once
#include <cstdint>


namespace core::runtime::Frame {
	bool Init();
	void Begin();
	void End();
	void Shutdown();
	void SetTargetFPS(int fps);
	double GetCurrentFPS();
	std::uint64_t GetFrameCount();
}