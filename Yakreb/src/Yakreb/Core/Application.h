#pragma once
#include "Yakreb/Core/Core.h"

#include "Yakreb/Events/ApplicationEvent.h"
#include "Yakreb/Core/Window.h"

namespace Yakreb {

	class Application {
		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event& event);

		private:
			bool OnWindowClose(WindowCloseEvent& event);

			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
	};
	
	// To be defined in client
	Application* CreateApplication();

}