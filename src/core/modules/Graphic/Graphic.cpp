#include "Graphic.h"
#include "core/runtime/Log/Log.h"
#include "core/modules/Window/Window.h"
#include <SDL3/SDL.h>
#include <string>

namespace core::modules::Graphic {
	namespace {
		bool Initialized = false;
		SDL_Window* WindowHandle = nullptr;
		SDL_GPUDevice* GPUDevice = nullptr;
	}
	bool Init() {


		if (Initialized)
			return true;


		// 获取窗口引用
		WindowHandle = core::modules::Window::GetNativeHandle();
		if (!WindowHandle) {
			core::runtime::Log::Error("Graphic initialization failed: window is unavailable");
			return false;
		}


		//创建GPU设备
		GPUDevice = SDL_CreateGPUDevice(
			SDL_GPU_SHADERFORMAT_SPIRV |
			SDL_GPU_SHADERFORMAT_DXIL,
			true,
			nullptr
		);

		if (!GPUDevice)
		{
			core::runtime::Log::Error(
				std::string("Failed to create GPU device: ") +
				SDL_GetError()
			);

			WindowHandle = nullptr;
			return false;
		}

		//把 GPU Device 连接到窗口
		if (!SDL_ClaimWindowForGPUDevice(
			GPUDevice,
			WindowHandle
		))
		{
			core::runtime::Log::Error(
				std::string("Failed to claim window for GPU: ") +
				SDL_GetError()
			);

			SDL_DestroyGPUDevice(GPUDevice);
			GPUDevice = nullptr;
			WindowHandle = nullptr;

			return false;
		}
		

		Initialized = true;

		// 打印 SDL 最终选择的后端
		const char* driver = SDL_GetGPUDeviceDriver(GPUDevice);
		core::runtime::Log::Debug(
			std::string("Graphic module initialized: GPU backend = ") +
			(driver ? driver : "unknown")
		);

		return true;
	}
	void Shutdown() {
		if (!Initialized)
			return;

		SDL_WaitForGPUIdle(GPUDevice);
		SDL_ReleaseWindowFromGPUDevice(
			GPUDevice,
			WindowHandle
		);
		SDL_DestroyGPUDevice(GPUDevice);

		GPUDevice = nullptr;
		WindowHandle = nullptr;
		Initialized = false;

		core::runtime::Log::Debug(
			"Graphic module shutdown"
		);
	}
}