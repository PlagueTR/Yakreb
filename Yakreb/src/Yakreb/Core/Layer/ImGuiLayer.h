#pragma once

#include "Yakreb/Core/Layer/Layer.h"

namespace Yakreb {

	class ImGuiLayer : public Layer {
		public:
			ImGuiLayer(const std::string& name = "Layer");
			virtual ~ImGuiLayer() = default;

			virtual void OnAttach() override;
			virtual void OnDetach() override;

			virtual void OnUpdate() override {}
			virtual void OnEvent(Event& event) override;

			virtual void OnImGuiRender() override {}

			void BeginRender();
			void EndRender();

			void	BlockEvents(bool block) {
				m_BlockEvents = block;
			}

		private:
			bool m_BlockEvents = true;

	};

}