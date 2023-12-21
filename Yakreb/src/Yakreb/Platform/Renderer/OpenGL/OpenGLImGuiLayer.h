#pragma once

#include "Yakreb/Core/Layer/ImGuiLayer.h"

namespace Yakreb {

	class OpenGLImGuiLayer : public ImGuiLayer {
		public:
			OpenGLImGuiLayer(const std::string& name = "Layer");
			virtual ~OpenGLImGuiLayer() = default;

			virtual void OnAttach() override;
			virtual void OnDetach() override;

			virtual void OnUpdate() override {}
			virtual void OnEvent(Event& event) override;

			virtual void OnImGuiRender() override {}

			virtual void BeginRender() override;
			virtual void EndRender() override;

	};

}