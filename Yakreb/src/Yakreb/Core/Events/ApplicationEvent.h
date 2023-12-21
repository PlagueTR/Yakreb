#pragma once

#include "Yakreb/Core/Events/Event.h"
#include "Yakreb/Core/PhysicalScreen.h"

namespace Yakreb {

	class ScreenEvent : public Event {
		public:
			inline int GetScreenID() const { return m_Screen.GetID(); }

			std::string GetScreenName() const { return m_Screen.GetName(); }

			uint32_t GetScreenWidth() const { return m_Screen.GetWidth(); }
			uint32_t GetScreenHeight() const { return m_Screen.GetHeight(); }
			glm::vec2 GetScreenResolution() const { return m_Screen.GetResolution(); }

			uint16_t GetScreenRefreshRate() const { return m_Screen.GetRefreshRate(); }

			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		protected:
			ScreenEvent(const PhysicalScreen& screen) : m_Screen(screen) {}
			PhysicalScreen m_Screen;
	};

	class ScreenConnectedEvent : public ScreenEvent {
		public:
			ScreenConnectedEvent(const PhysicalScreen& screen) : ScreenEvent(screen) {}

			virtual inline std::string ToString() const override {
				return fmt::format("ScreenConnectedEvent: {} - \"{}\" - ({}, {}) {}Hz",
					GetScreenID(), GetScreenName(), GetScreenWidth(), GetScreenHeight(),
					GetScreenRefreshRate());
			}

			EVENT_CLASS_TYPE(ScreenConnected)
	};

	class ScreenDisconnectedEvent : public ScreenEvent {
		public:
			ScreenDisconnectedEvent(const PhysicalScreen& screen) : ScreenEvent(screen) {}

			virtual inline std::string ToString() const override {
				return fmt::format("ScreenDisconnectedEvent: {} - \"{}\" - ({}, {}) {}Hz",
					GetScreenID(), GetScreenName(), GetScreenWidth(), GetScreenHeight(),
					GetScreenRefreshRate());
			}

			EVENT_CLASS_TYPE(ScreenDisconnected)
	};

	class WindowResizedEvent : public Event {
		public:
			WindowResizedEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

			uint32_t GetWidth() const { return m_Width; }
			uint32_t GetHeight() const { return m_Height; }

			virtual inline std::string ToString() const override {
				return fmt::format("WindowResizedEvent: {}, {}", m_Width, m_Height);
			}

			EVENT_CLASS_TYPE(WindowResized)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		private:
			uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
		public:
			WindowCloseEvent() = default;

			virtual inline std::string ToString() const override {
				return "WindowClosedEvent";
			}

			EVENT_CLASS_TYPE(WindowClosed)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowFocusEvent : public Event {
		public:
			WindowFocusEvent() = default;

			virtual inline std::string ToString() const override {
				return "WindowFocusEvent";
			}

			EVENT_CLASS_TYPE(WindowFocus)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowLostFocusEvent : public Event {
		public:
			WindowLostFocusEvent() = default;

			virtual inline std::string ToString() const override {
				return "WindowLostFocusEvent";
			}

			EVENT_CLASS_TYPE(WindowLostFocus)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event {
		public:
			AppTickEvent() = default;

			virtual inline std::string ToString() const override {
				return "AppTickEvent";
			}

			EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event {
		public:
			AppUpdateEvent() = default;

			virtual inline std::string ToString() const override {
				return "AppUpdateEvent";
			}

			EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event {
		public:
			AppRenderEvent() = default;

			virtual inline std::string ToString() const override {
				return "AppRenderEvent";
			}

			EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}