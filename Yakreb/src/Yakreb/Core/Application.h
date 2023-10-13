#pragma once
#include "Yakreb/Core/Core.h"

namespace Yakreb {

	class Application {
		public:
			Application();
			virtual ~Application();

			void Run();
	};
	
	// To be defined in client
	Application* CreateApplication();

}