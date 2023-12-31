#pragma once
#include "Yakreb/Renderer/RendererAPI.h"

namespace Yakreb {

	class OpenGLRendererAPI : public RendererAPI {
		public:
			virtual void InitImpl() override;
			virtual void ShutdownImpl() override;

			virtual void SetClearColorImpl(const glm::vec4& color) override;
			virtual void ClearImpl() override;

			virtual void DrawIndexedImpl(const Ref<VertexArray>& vertexArray) override;
	};

}