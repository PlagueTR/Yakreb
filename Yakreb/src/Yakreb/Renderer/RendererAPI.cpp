#include "yakrebpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Yakreb {

	RendererAPI* RendererAPI::s_Instance = nullptr;
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;

	void RendererAPI::SetAPI(API api) {
		// For now we just set the API before it's initialized
		// Later we could implement methods to swap rendering APIs
		if (s_Instance)
			delete s_Instance;

		switch (api) {
			default:
				YGE_CORE_ERROR("{}", "Renderer API can not be None, defaulting to OpenGL");
				[[fallthrough]];
			case API::OpenGL:
				s_API = API::OpenGL;
				s_Instance = new OpenGLRendererAPI();
				break;
		}
	}

}