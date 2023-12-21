#pragma once

#include "Yakreb/Core/Core.h"

#include <string>
#include <functional>
#include <spdlog/fmt/fmt.h>

namespace Yakreb {

	// Events are currently blocking, meaning they get dispatched immediately

	enum class EventType {
		None = 0,
		// Application
		ScreenConnected, ScreenDisconnected, 
		WindowClosed, WindowResized, WindowFocus, WindowLostFocus,
		// Input
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		ControllerConnected, ControllerDisconnected, // no events for joystick button -  axis - hat state changes
		// Future
		AppTick, AppUpdate, AppRender,
		NetworkConnected, NetworkDisconnected,
		ClipboardCopy, ClipboardPaste
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4),
		EventCategoryController     = BIT(5),
		EventCategoryNetwork        = BIT(6),
		EventCategoryClipboard      = BIT(7)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char *GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event {
		public:
			virtual ~Event() = default;

			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;
			virtual int GetCategoryFlags() const = 0;
			virtual inline std::string ToString() const { return GetName(); }

			bool IsInCategory(EventCategory category) {
				return GetCategoryFlags() & category;
			}

			bool Handled = false;
		private:
			friend class EventDispatcher;
	};

	class EventDispatcher {
		public:
			EventDispatcher(Event &event) : m_Event(event){}

			template<typename T, typename F>
			bool Dispatch(const F& function) {
				if (m_Event.GetEventType() == T::GetStaticType()) {
					m_Event.Handled = function(static_cast<T&>(m_Event));
					return true;
				}
				return false;
			}
		private:
			Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}