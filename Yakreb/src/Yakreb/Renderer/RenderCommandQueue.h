#pragma once

#include "Yakreb/Core/Core.h"


namespace Yakreb {

	class RenderCommandQueue {
		public:
			typedef void(*RenderCommandFn)(void*);

			RenderCommandQueue();
			~RenderCommandQueue();

			void* Allocate(RenderCommandFn function, uint32_t size);

			void Execute();

			uint32_t GetCapacity() { return m_Capacity; }
			void Shrink() { m_ShouldShrink = true; }

		private:
			void Resize(uint32_t currentSize, uint32_t newSize);
			static uint32_t GetClosestPow2(uint32_t num);

			byte* m_CommandBuffer;
			byte* m_CommandBufferPtr;
			uint32_t m_Capacity;
			uint32_t m_CommandCount = 0;
			bool m_ShouldShrink = false;

			static const uint32_t s_InitialBufferSize = 1024;

	};

}