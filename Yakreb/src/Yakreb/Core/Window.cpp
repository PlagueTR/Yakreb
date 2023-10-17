#include "yakrebpch.h"
#include "Window.h"

#ifdef YGE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#elif defined(YGE_PLATFORM_LINUX)
	#include "Platform/Linux/LinuxWindow.h"
#endif

namespace Yakreb {

	bool Window::s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties) {

		#ifdef YGE_PLATFORM_WINDOWS
			return new WindowsWindow(properties);
		#elif defined(YGE_PLATFORM_LINUX)
			return new LinuxWindow(properties);
		#endif
		return nullptr;

	}

}