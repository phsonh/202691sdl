#pragma once


namespace core::modules::Window {
	struct Engine_Window;
	Engine_Window* Create(int width, int height);
	bool SetTitle(Engine_Window* window, const char* title);
	bool SetSize(Engine_Window* window, int width, int height);
	void Destroy(Engine_Window*& window);
}