#pragma once

#include "Yakreb/Renderer/RendererAPI.h"
#include "Yakreb/Renderer/RenderCommandQueue.h"

#include "Yakreb/Renderer/Camera.h"
#include "Yakreb/Renderer/Shader.h"

namespace Yakreb {

	class Renderer {
		public:
			static void Init();
			static void Shutdown();

			static void BeginScene(const Camera& camera);
			static void EndScene();

			template <typename FuncT>
			static void Submit(FuncT&& function) {
				auto renderCmd = [](void* ptr) {
					auto funcPtr = (FuncT*)ptr;
					(*funcPtr)();
					funcPtr->~FuncT();
				};
				auto storageBuffer = GetRenderCommandQueue().Allocate(renderCmd, sizeof(function));
				new (storageBuffer) FuncT(std::forward<FuncT>(function));
			}
			
			static void SetClearColor(const glm::vec4& color);
			static void Clear();

			static void Draw(Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

			static uint32_t GetRenderCommandQueueIndex();
			static uint32_t GetRenderCommandQueueSubmissionIndex();
			static void SwapRenderCommandQueues();

			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		private:
			static RenderCommandQueue& GetRenderCommandQueue();

			static RenderCommandQueue** s_RenderCommandQueue;
			static std::atomic<uint32_t> s_RenderCommandQueueSubmissionIndex;

			static glm::mat4 s_CameraViewProjectionMatrix;

			static const uint32_t s_RenderCommandQueueCount = 2;
			static const std::string s_UniformViewProjection;
			static const std::string s_UniformTransform;

	};

}
