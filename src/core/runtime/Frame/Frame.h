#pragma once
#include <cstdint>


namespace core::runtime::Frame {
	void Init();
	void Begin();
	void End();
	bool IsRunning();
	void Break();
	void SetTargetFPS(int fps);
	double GetCurrentFPS();
	std::uint64_t GetFrameCount();
}