#pragma once
#include "Yakreb/Core/Core.h"

#include "Yakreb/Core/Events/ApplicationEvent.h"
#include "Yakreb/Core/Window.h"
#include "Yakreb/Core/Layer/ImGuiLayer.h"
#include "Yakreb/Core/Layer/LayerStack.h"

int main(int argc, char** argv);

namespace Yakreb {

	class Application {
		public:
			Application(const std::string &name = "Yakreb Application");
			virtual ~Application() = default;

			void OnEvent(Event& event);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);

			void PopLayer(Layer* layer);
			void PopOverlay(Layer* overlay);

			static Application& Get() { return *s_Instance; }
			inline Window& GetWindow() { return *m_Window; }

		private:
			void Run();

			bool OnWindowClose(WindowCloseEvent& event);

			static Application* s_Instance;
			Scope<Window> m_Window;

			bool m_Running = true;

			LayerStack m_LayerStack;
			ImGuiLayer* m_ImGuiLayer;
			
			friend int ::main(int argc, char** argv);
	};
	
	// To be defined in client
	Application* CreateApplication();

}