#include "yakrebpch.h"
#include "Renderer.h"

namespace Yakreb {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera) {
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		(static_cast<Ref<Shader>>(shader))->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		(static_cast<Ref<Shader>>(shader))->SetMat4("u_Transform", transform);

		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}

}