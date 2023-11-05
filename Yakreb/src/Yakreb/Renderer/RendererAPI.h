#pragma once

#include "Yakreb/Renderer/VertexArray.h"

#include <string>
#include <glm/glm.hpp>

namespace Yakreb {

	namespace CoreError {
		inline static const char* YGE_NONE_RENDERER_API = "Renderer API was None, defaulting to OpenGL";
	}

	class RendererAPI {
		public:
			enum class API {
				None = 0,
				OpenGL = 1
			};

			virtual ~RendererAPI() = default;

			static void Init() { s_Instance->InitImpl(); }

			inline static void SetClearColor(const glm::vec4& color) { s_Instance->SetClearColorImpl(color); }
			inline static void Clear() { s_Instance->ClearImpl(); }

			inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_Instance->DrawIndexedImpl(vertexArray); }

			inline static API GetAPI() { return s_API; }
			static void SetAPI(API api);

		protected:
			virtual void InitImpl() = 0;
			
			virtual void SetClearColorImpl(const glm::vec4& color) = 0;
			virtual void ClearImpl() = 0;

			virtual void DrawIndexedImpl(const Ref<VertexArray>& vertexArray) = 0;

			static RendererAPI* s_Instance;
			static API s_API;

	};

}