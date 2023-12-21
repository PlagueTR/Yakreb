#pragma once

#include "Yakreb/Core/Layer/Layer.h"

namespace Yakreb {

	class ImGuiLayer : public Layer {
		public:
			ImGuiLayer(const std::string& name) : Layer(name + " (ImGui") {}
			virtual void BeginRender() = 0;
			virtual void EndRender() = 0;

			void BlockEvents(bool block) {
				m_BlockEvents = block;
			}

			static ImGuiLayer* Create(const std::string& name = "Layer");

		protected:
			bool m_BlockEvents = true;

	};

}