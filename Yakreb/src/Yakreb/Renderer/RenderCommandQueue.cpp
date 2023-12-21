#include "yakrebpch.h"
#include "RenderCommandQueue.h"

namespace Yakreb {

	RenderCommandQueue::RenderCommandQueue() : m_Capacity(s_InitialBufferSize) {
		m_CommandBuffer = ygenew("RenderCommandQueue") byte[s_InitialBufferSize];
		m_CommandBufferPtr = m_CommandBuffer;
		std::memset(m_CommandBuffer, 0, s_InitialBufferSize);
	}

	RenderCommandQueue::~RenderCommandQueue() {
		delete[] m_CommandBuffer;
	}

	void* RenderCommandQueue::Allocate(RenderCommandFn function, uint32_t size) {

		uint32_t currentSize = static_cast<uint32_t>(m_CommandBufferPtr - m_CommandBuffer);
		uint32_t addedSize = sizeof(RenderCommandFn) + sizeof(uint32_t) + size;
		if (currentSize + addedSize > m_Capacity)
			Resize(currentSize, m_Capacity * 2);

		*(RenderCommandFn*)m_CommandBufferPtr = function;
		m_CommandBufferPtr += sizeof(RenderCommandFn);
		
		*(uint32_t*)m_CommandBufferPtr = size;
		m_CommandBufferPtr += sizeof(uint32_t);

		void* memory = m_CommandBufferPtr;
		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;

	}

	void RenderCommandQueue::Execute() {

		byte* buffer = m_CommandBuffer;

		for (uint32_t i = 0; i < m_CommandCount; i++) {
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			uint32_t size = *(uint32_t*)buffer;
			buffer += sizeof(uint32_t);

			function(buffer);
			buffer += size;
		}

		if (m_ShouldShrink) {
			uint32_t currentSize = static_cast<uint32_t>(m_CommandBufferPtr - m_CommandBuffer);
			Resize(0, GetClosestPow2(currentSize));
			m_ShouldShrink = false;
		}

		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;

	}

	void RenderCommandQueue::Resize(uint32_t currentSize, uint32_t newSize) {
		m_Capacity = newSize;

		byte* newBuffer = ygenew("RenderComamndQueue") byte[newSize];
		std::memcpy(newBuffer, m_CommandBuffer, currentSize);
		delete[] m_CommandBuffer;
		m_CommandBuffer = newBuffer;
		m_CommandBufferPtr = newBuffer + currentSize;
	}

	uint32_t RenderCommandQueue::GetClosestPow2(uint32_t num) {
		// if num is a power of 2
		if ((num & (num - 1)) == 0) {
			return num;
		}

		uint8_t pos = 0;
		for (uint8_t i = 0; i < 32; ++i) {
			if (num <= (1u << i)) {
				pos = i;
				break;
			}
		}

		for (uint8_t i = pos; i > 0; --i) {
			num |= (1 << (i - 1));
		}

		return std::max(num, s_InitialBufferSize);

	}

}