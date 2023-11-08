#pragma once

#include "Yakreb/Core/Events/Event.h"
#include "Yakreb/Core/Input/KeyCodes.h"

namespace Yakreb {

	class KeyEvent : public Event {
		public:
			inline KeyCode GetKeyCode() const { return m_KeyCode; }

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		protected:
			KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}
			KeyCode m_KeyCode;
	};

	class  KeyPressedEvent : public KeyEvent {
		public:
			KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

			inline uint16_t GetRepeatCount() const { return m_RepeatCount; }

			virtual inline std::string ToString() const override {
				return fmt::format("KeyPressedEvent: {} ({} repeats)", GetKeyName(m_KeyCode), m_RepeatCount);
			}

			EVENT_CLASS_TYPE(KeyPressed)
		private:
			uint16_t m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyEvent {
		public:
			KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

			virtual inline std::string ToString() const override {
				return fmt::format("KeyReleasedEvent: {}", GetKeyName(m_KeyCode));
			}

			EVENT_CLASS_TYPE(KeyReleased)
	};

	class  KeyTypedEvent : public KeyEvent {
		public:
			KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

			virtual inline std::string ToString() const override {
				return fmt::format("KeyTypedEvent: {}", GetUTF8(static_cast<const unsigned int>(m_KeyCode)));
			}

			EVENT_CLASS_TYPE(KeyTyped)
	};

}