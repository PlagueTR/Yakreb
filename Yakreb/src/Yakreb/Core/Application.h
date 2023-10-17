#pragma once
#include "Yakreb/Core/Core.h"

#include "Yakreb/Events/ApplicationEvent.h"
#include "Yakreb/Core/Window.h"

int main(int argc, char** argv);

namespace Yakreb {

	class Application {
		public:
			Application(const std::string &name = "Yakreb Application");
			virtual ~Application();

			void OnEvent(Event& event);

			static Application& Get() { return *s_Instance; }
			Window& GetWindow() { return *m_Window; }

		private:
			void Run();

			bool OnWindowClose(WindowCloseEvent& event);

			static Application* s_Instance;
			Scope<Window> m_Window;

			bool m_Running = true;
			
			friend int ::main(int argc, char** argv);
	};
	
	// To be defined in client
	Application* CreateApplication();

}