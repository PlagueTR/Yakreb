#include "yakrebpch.h"
#include "Shader.h"

#include "Yakreb/Renderer/RendererAPI.h"

#include "Yakreb/Platform/OpenGL/OpenGLShader.h"

namespace Yakreb {

	Shader* Shader::Create(const std::string& path) {

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(path);
		}

	}

	Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(name, vertexSrc, fragmentSrc);
		}

	}

}