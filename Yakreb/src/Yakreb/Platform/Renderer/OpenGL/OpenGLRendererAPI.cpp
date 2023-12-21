#include "yakrebpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Yakreb {

	void OpenGLRendererAPI::InitImpl() {
		s_DeviceInfo.Vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		s_DeviceInfo.Device = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		s_DeviceInfo.Version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		LogRendererInfo();
	}

	void OpenGLRendererAPI::ShutdownImpl() {

	}

	void OpenGLRendererAPI::SetClearColorImpl(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::ClearImpl() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexedImpl(const Ref<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}