#include "yakrebpch.h"
#include "Renderer.h"

namespace Yakreb {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera) {
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		shader->SetMat4(s_UniformViewProjection, s_SceneData->ViewProjectionMatrix);
		shader->SetMat4(s_UniformTransform, transform);

		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}

}