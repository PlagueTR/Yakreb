#include "yakrebpch.h"
#include "Renderer.h"

namespace Yakreb {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera) {
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Shader* shader, const VertexArray* vertexArray, const glm::mat4& transform) {
		shader->Bind();
		((Shader *)shader)->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		((Shader *)shader)->SetMat4("u_Transform", transform);

		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}

}