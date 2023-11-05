#pragma once

#include "Yakreb/Renderer/RendererAPI.h"

namespace Yakreb {

	class RenderCommand {
		public:
			inline static void SetClearColor(const glm::vec4& color) {
				RendererAPI::SetClearColor(color);
			}

			inline static void Clear() {
				RendererAPI::Clear();
			}

			inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
				RendererAPI::DrawIndexed(vertexArray);
			}

	};

}