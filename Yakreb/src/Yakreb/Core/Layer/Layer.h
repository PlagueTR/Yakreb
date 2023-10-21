#pragma once

#include "Yakreb/Core/Events/Event.h"

#include <string>

namespace Yakreb {

	class Layer {
		public:
			Layer(const std::string& name = "Layer");
			virtual ~Layer() = default;

			virtual void OnAttach() {}
			virtual void OnDetach() {}

			virtual void OnUpdate() {}
			virtual void OnEvent(Event& event) {}

			virtual void OnImGuiRender() {}

			const std::string& GetName() const { return m_LayerName; }

		protected:
			std::string m_LayerName;

	};

}