#pragma once

#include "Yakreb/Core/PhysicalScreen.h"

struct GLFWmonitor;

namespace Yakreb {

	class LinuxPhysicalScreen : public PhysicalScreen {
		public:
			LinuxPhysicalScreen(int id, GLFWmonitor* monitor);

			void Init();

		private:
			GLFWmonitor* m_Monitor;

			int m_RedBits, m_GreenBits, m_BlueBits;

			friend class LinuxWindow;

	};

}