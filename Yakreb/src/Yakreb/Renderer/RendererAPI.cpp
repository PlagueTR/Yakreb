#include "yakrebpch.h"
#include "RendererAPI.h"

#include "Yakreb/Platform/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Yakreb {

	RendererAPI* RendererAPI::s_Instance = nullptr;
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;

	void RendererAPI::SetAPI(API api) {

		delete s_Instance;

		switch (api) {
			default:
				YGE_CORE_ASSERT(false, CoreError::Renderer::YGE_NONE_RENDERER_API);
				[[fallthrough]];
			case API::OpenGL:
				s_API = API::OpenGL;
				s_Instance = new OpenGLRendererAPI();
				break;
		}

	}

}