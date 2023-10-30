#include "yakrebpch.h"
#include "VertexArray.h"

#include "Yakreb/Renderer/RendererAPI.h"

#include "Yakreb/Platform/OpenGL/OpenGLVertexArray.h"

namespace Yakreb {

	VertexArray* VertexArray::Create() {

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}

	}

}