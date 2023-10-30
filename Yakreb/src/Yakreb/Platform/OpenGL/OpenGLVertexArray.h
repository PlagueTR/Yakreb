#pragma once

#include "Yakreb/Renderer/VertexArray.h"

namespace Yakreb {

	class OpenGLVertexArray : public VertexArray {
		public:
			OpenGLVertexArray();
			~OpenGLVertexArray();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void AddVertexBuffer(const VertexBuffer* vertexBuffer) override;
			virtual void SetIndexBuffer(const IndexBuffer* indexBuffer) override;

			virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const override { return m_VertexBuffers; }
			virtual const IndexBuffer* GetIndexBuffer() const override { return m_IndexBuffer; }

		private:
			uint32_t m_RendererID;
			std::vector<VertexBuffer*> m_VertexBuffers;
			IndexBuffer* m_IndexBuffer;

	};

}