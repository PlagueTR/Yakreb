#pragma once

#include "Yakreb/Core/Events/Event.h"
#include "Yakreb/Core/Input/MouseButtonCodes.h"

namespace Yakreb {

	class MouseMovedEvent : public Event {
		public:
			MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

			float GetX() const { return m_MouseX; }
			float GetY() const { return m_MouseY; }

			virtual inline std::string ToString() const override {
				return fmt::format("MouseMovedEvent: {}, {}", m_MouseX, m_MouseY);
			}

			EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
		public:
			MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

			float GetXOffset() const { return m_XOffset; }
			float GetYOffset() const { return m_YOffset; }

			virtual inline std::string ToString() const override {
				return fmt::format("MouseScrolledEvent: {}, {}", m_XOffset, m_YOffset);
			}

			EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event {
		public:
			inline MouseButton GetMouseButton() const { return m_Button; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		protected:
			MouseButtonEvent(const MouseButton button) : m_Button(button) {}

			MouseButton m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
		public:
			MouseButtonPressedEvent(const MouseButton button) : MouseButtonEvent(button) {}

			virtual inline std::string ToString() const override {
				return fmt::format("MouseButtonPressedEvent: {}", GetMouseButtonName(m_Button));
			}

			EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class  MouseButtonReleasedEvent : public MouseButtonEvent {
		public:
			MouseButtonReleasedEvent(const MouseButton button) : MouseButtonEvent(button) {}

			virtual inline std::string ToString() const override {
				return fmt::format("MouseButtonReleasedEvent: {}", GetMouseButtonName(m_Button));
			}

			EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}