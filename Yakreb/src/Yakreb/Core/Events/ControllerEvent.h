#pragma once

#include "Yakreb/Core/Events/Event.h"
#include "Yakreb/Core/Input/Controller.h"

namespace Yakreb {

	class ControllerEvent : public Event {
		public:
			inline int GetControllerID() const { return m_Controller.ID; }
			std::string GetControllerName() const { return m_Controller.Name; }

			EVENT_CLASS_CATEGORY(EventCategoryController | EventCategoryInput)
		protected:
			ControllerEvent(const Controller& controller) : m_Controller(controller) {}
			Controller m_Controller;
	};

	class ControllerConnectedEvent : public ControllerEvent {
		public:
			ControllerConnectedEvent(const Controller& controller) : ControllerEvent(controller) {}

			virtual inline std::string ToString() const override {
				return fmt::format("ControllerConnectedEvent: Controller{} - {}", m_Controller.ID, m_Controller.Name);
			}

			EVENT_CLASS_TYPE(ControllerConnected)
	};

	class ControllerDisconnectedEvent : public ControllerEvent {
		public:
			ControllerDisconnectedEvent(const Controller& controller) : ControllerEvent(controller) {}

			virtual inline std::string ToString() const override {
				return fmt::format("ControllerDisconnectedEvent: Controller{} - {}", m_Controller.ID, m_Controller.Name);
			}

			EVENT_CLASS_TYPE(ControllerDisconnected)
	};

}