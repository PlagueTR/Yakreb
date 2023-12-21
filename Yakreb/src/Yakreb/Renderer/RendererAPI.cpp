#include "yakrebpch.h"
#include "RendererAPI.h"

#include "Yakreb/Platform/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Yakreb {

	RendererAPI* RendererAPI::s_Instance = nullptr;
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;
	RendererAPI::DeviceInfo RendererAPI::s_DeviceInfo{};

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

	void RendererAPI::LogRendererInfo() {
		switch (GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::Renderer::YGE_NONE_RENDERER_API);
				SetAPI(API::OpenGL);
				[[fallthrough]];
			case API::OpenGL:
				YGE_CORE_INFO("OpenGL Info:");
		}
		YGE_CORE_INFO("  Vendor: {0}", s_DeviceInfo.Vendor);
		YGE_CORE_INFO("  Device: {0}", s_DeviceInfo.Device);
		YGE_CORE_INFO("  Version: {0}", s_DeviceInfo.Version);
	}

}