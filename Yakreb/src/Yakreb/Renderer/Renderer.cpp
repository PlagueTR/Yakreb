#include "yakrebpch.h"
#include "Renderer.h"

#include "Yakreb/Core/Application.h"
#include "GLFW/glfw3.h"

namespace Yakreb {

	const std::string Renderer::s_UniformViewProjection = "u_ViewProjection";
	const std::string Renderer::s_UniformTransform = "u_Transform";

	RenderCommandQueue** Renderer::s_RenderCommandQueue = nullptr;
	std::atomic<uint32_t> Renderer::s_RenderCommandQueueSubmissionIndex = 0;

	glm::mat4 Renderer::s_CameraViewProjectionMatrix = glm::mat4(1.0f);

	void Renderer::Init() {
		RendererAPI::Init();
		s_RenderCommandQueue = new RenderCommandQueue*[s_RenderCommandQueueCount];
		for (uint32_t i = 0; i < s_RenderCommandQueueCount; i++)
			s_RenderCommandQueue[i] = new RenderCommandQueue();
	}

	void Renderer::Shutdown() {
		for (uint32_t i = 0; i < s_RenderCommandQueueCount; i++)
			delete s_RenderCommandQueue[i];
		delete[] s_RenderCommandQueue;
	}

	void Renderer::BeginScene(const Camera& camera) {
		s_CameraViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {
		s_RenderCommandQueue[GetRenderCommandQueueIndex()]->Execute();
		SwapRenderCommandQueues();
	}

	void Renderer::SetClearColor(const glm::vec4& color) {
		Submit([color]() {
			RendererAPI::SetClearColor(color);
		});
	}

	void Renderer::Clear() {
		Submit([]() {
			RendererAPI::Clear();
		});
	}

	void Renderer::Draw(Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		Submit([&shader, &vertexArray, &transform]() {
			shader->Bind();
			shader->SetMat4(s_UniformViewProjection, s_CameraViewProjectionMatrix);
			shader->SetMat4(s_UniformTransform, transform);
			vertexArray->Bind();
			RendererAPI::DrawIndexed(vertexArray);
		});
	}

	RenderCommandQueue& Renderer::GetRenderCommandQueue() {
		return *s_RenderCommandQueue[s_RenderCommandQueueSubmissionIndex];
	}

	uint32_t Renderer::GetRenderCommandQueueIndex() {
		return (s_RenderCommandQueueSubmissionIndex + 1) % s_RenderCommandQueueCount;
	}

	uint32_t Renderer::GetRenderCommandQueueSubmissionIndex() {
		return s_RenderCommandQueueSubmissionIndex;
	}

	void Renderer::SwapRenderCommandQueues() {
		s_RenderCommandQueueSubmissionIndex = (s_RenderCommandQueueSubmissionIndex + 1) % s_RenderCommandQueueCount;
	}

}