#include "yakrebpch.h"
#include "Window.h"

#ifdef YGE_PLATFORM_WINDOWS
	#include "Yakreb/Platform/Windows/WindowsWindow.h"
#elif defined(YGE_PLATFORM_LINUX)
	#include "Yakreb/Platform/Linux/LinuxWindow.h"
#endif

namespace Yakreb {

	uint8_t Window::s_GLFWWindowCount = 0;

	Scope<Window> Window::Create(const WindowProperties& properties) {

		#ifdef YGE_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(properties);
		#elif defined(YGE_PLATFORM_LINUX)
			return CreateScope<LinuxWindow>(properties);
		#endif
		return nullptr;

	}

}