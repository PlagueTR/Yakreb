#pragma once

#include "Yakreb/Renderer/RenderCommand.h"

#include "Yakreb/Renderer/Camera.h"
#include "Yakreb/Renderer/Shader.h"

namespace Yakreb {

	class Renderer {
		public:
			static void BeginScene(OrthographicCamera& camera);
			static void EndScene();

			static void Submit(Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		private:
			struct SceneData {
				glm::mat4 ViewProjectionMatrix;
			};

			static SceneData* s_SceneData;

			inline static const std::string s_UniformViewProjection = "u_ViewProjection";
			inline static const std::string s_UniformTransform = "u_Transform";

	};

}
