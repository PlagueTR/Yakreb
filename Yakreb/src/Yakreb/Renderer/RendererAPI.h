#pragma once

#include "Yakreb/Renderer/VertexArray.h"

#include <string>
#include <glm/glm.hpp>

namespace Yakreb {

	class RendererAPI {
		public:
			enum class API {
				None = 0,
				OpenGL
			};

			struct DeviceInfo {
				std::string Vendor;
				std::string Device;
				std::string Version;
			};

			virtual ~RendererAPI() = default;

			static void Init() { s_Instance->InitImpl(); }
			static void Shutdown() { s_Instance->ShutdownImpl(); }

			static void LogRendererInfo();

			inline static void SetClearColor(const glm::vec4& color) { s_Instance->SetClearColorImpl(color); }
			inline static void Clear() { s_Instance->ClearImpl(); }

			inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_Instance->DrawIndexedImpl(vertexArray); }

			inline static API GetAPI() { return s_API; }
			static void SetAPI(API api);

		protected:
			virtual void InitImpl() = 0;
			virtual void ShutdownImpl() = 0;
			
			virtual void SetClearColorImpl(const glm::vec4& color) = 0;
			virtual void ClearImpl() = 0;

			virtual void DrawIndexedImpl(const Ref<VertexArray>& vertexArray) = 0;

			static RendererAPI* s_Instance;
			static API s_API;
			static DeviceInfo s_DeviceInfo;

	};

}