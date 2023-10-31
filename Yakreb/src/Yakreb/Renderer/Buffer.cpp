#include "yakrebpch.h"
#include "Buffer.h"

#include "Yakreb/Renderer/RendererAPI.h"

#include "Yakreb/Platform/OpenGL/OpenGLBuffer.h"

namespace Yakreb {

	void BufferLayout::CalculateOffsetAndStride() {
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements) {
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t count) {

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, count);
		}

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
		}

	}

}