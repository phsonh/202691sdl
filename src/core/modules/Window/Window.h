#pragma once


namespace core::modules::Window {
	bool Init(int width, int height);
	bool SetTitle(const char* title);
	void Shutdown();
}