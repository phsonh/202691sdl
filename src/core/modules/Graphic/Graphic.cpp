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

	bool RenderFrame() {
		// 从 GPUDevice 取得一份空命令表，
		// 并把它的指针保存到 commandBuffer
		SDL_GPUCommandBuffer* commandBuffer =
			SDL_AcquireGPUCommandBuffer(GPUDevice);


		// 检测命令表是否获取成功
		if (!commandBuffer) {
			core::runtime::Log::Error(
				std::string("Failed to acquire GPU command buffer: ") +
				SDL_GetError()
			);
			return false;
		}

		// 初始化一个SwapchainTexture指针用于接受SwapchainTexture地址
		SDL_GPUTexture* swapchainTexture = nullptr;
		// SDL 会把它改成某张可用 SwapchainTexture 的地址
		if (!SDL_WaitAndAcquireGPUSwapchainTexture(
			commandBuffer,
			WindowHandle,
			&swapchainTexture,
			nullptr,
			nullptr
		)) {
			// SDL 调用发生错误
			core:runtime::Log::Error(
				std::string("Failed to acquire swapchain texture: ") +
				SDL_GetError()
			);
			SDL_CancelGPUCommandBuffer(commandBuffer);
			return false;
		}


		// 没有画布(窗口最小化)
		if (!swapchainTexture)
		{
			// 提交一张空渲染任务单
			if (!SDL_SubmitGPUCommandBuffer(commandBuffer))
			{
				// 提交失败，通过 SDL_GetError() 获取原因
				core::runtime::Log::Error(
					std::string("Failed to submit empty command buffer: ") +
					SDL_GetError()
				);

				return false;
			}
			// 本帧虽然没有画面，但这是窗口最小化导致的正常跳过
			return true;
		}


		SDL_GPUColorTargetInfo colorTarget{};
		// 指定本次 RenderPass 的目标是刚取得的窗口画布
		colorTarget.texture = swapchainTexture;

		colorTarget.clear_color = {
			0.05f,
			0.08f,
			0.15f,
			1.0f
		};
		colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
		colorTarget.store_op = SDL_GPU_STOREOP_STORE;

		// 在指定的一组目标纹理上，连续执行一批图形绘制命令的阶段
		SDL_GPURenderPass* renderPass =
			SDL_BeginGPURenderPass(
				commandBuffer,
				&colorTarget,
				1,
				nullptr
			);
		SDL_EndGPURenderPass(renderPass);
		if (!SDL_SubmitGPUCommandBuffer(commandBuffer))
		{
			core::runtime::Log::Error(
				std::string("Failed to submit GPU command buffer: ") +
				SDL_GetError()
			);

			return false;
		}

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