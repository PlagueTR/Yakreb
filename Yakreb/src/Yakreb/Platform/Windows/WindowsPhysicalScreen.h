#pragma once

#include "Yakreb/Core/PhysicalScreen.h"

struct GLFWmonitor;

namespace Yakreb {

	class WindowsPhysicalScreen : public PhysicalScreen {
		public:
			WindowsPhysicalScreen(int id, GLFWmonitor* monitor);

			void Init();

		private:
			GLFWmonitor* m_Monitor;

			int m_RedBits, m_GreenBits, m_BlueBits;

			friend class WindowsWindow;

	};

}