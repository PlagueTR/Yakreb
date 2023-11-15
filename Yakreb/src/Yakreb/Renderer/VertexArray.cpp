#include "yakrebpch.h"
#include "VertexArray.h"

#include "Yakreb/Renderer/RendererAPI.h"

#include "Yakreb/Platform/Renderer/OpenGL/OpenGLVertexArray.h"

namespace Yakreb {

	Ref<VertexArray> VertexArray::Create() {

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::Renderer::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				return Ref<OpenGLVertexArray>::Create();
		}

	}

}