#pragma once

#include <glm/glm.hpp>

namespace Yakreb {

	class RendererAPI {
		public:
			enum class API {
				None = 0,
				OpenGL = 1
			};

			virtual ~RendererAPI() = default;

			static void Init() { s_Instance->InitImpl(); }

			static void SetClearColor(const glm::vec4& color) { s_Instance->SetClearColorImpl(color); }
			static void Clear() { s_Instance->ClearImpl(); }

			inline static API GetAPI() { return s_API; }
			static void SetAPI(API api);

		protected:
			virtual void InitImpl() = 0;
			
			virtual void SetClearColorImpl(const glm::vec4& color) = 0;
			virtual void ClearImpl() = 0;

			static RendererAPI* s_Instance;
			static API s_API;

	};

}