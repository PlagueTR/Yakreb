#pragma once

#include "Yakreb/Core/Events/Event.h"

namespace Yakreb {

	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

			uint32_t GetWidth() const { return m_Width; }
			uint32_t GetHeight() const { return m_Height; }

			virtual inline std::string ToString() const override {
				return fmt::format("WindowResizedEvent: {}, {}", m_Width, m_Height);
			}

			EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		private:
			uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
		public:
			WindowCloseEvent() = default;

			EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event {
		public:
			AppTickEvent() = default;

			EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event {
		public:
			AppUpdateEvent() = default;

			EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event {
		public:
			AppRenderEvent() = default;

			EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}