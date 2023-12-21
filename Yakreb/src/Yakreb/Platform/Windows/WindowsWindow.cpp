#include "yakrebpch.h"
#include "WindowsWindow.h"

#include "Yakreb/Core/Events/ApplicationEvent.h"
#include "Yakreb/Core/Events/KeyEvent.h"
#include "Yakreb/Core/Events/MouseEvent.h"
#include "Yakreb/Core/Events/ControllerEvent.h"

#include "Yakreb/Platform/Windows/WindowsPhysicalScreen.h"

#include "Yakreb/Platform/Renderer/OpenGL/OpenGLContext.h"

#include "Yakreb/Core/Input/Input.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	WindowsWindow::WindowsWindow(const WindowSpecification& specification) {
		Init(specification);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowSpecification& specification) {
		m_Data.Title = specification.Title;
		m_Data.Width = specification.Width;
		m_Data.Height = specification.Height;
		m_Data.MonitorPreference = specification.MonitorPreference;
		m_Data.Decorated = specification.Decorated;
		m_Data.Resizable = specification.Resizable;
		m_Data.Fullscreen = specification.Fullscreen;
		m_Data.StartMaximized = specification.StartMaximized;
		m_Data.VSync = specification.VSync;

		if (!s_GLFWWindowCount) {
			glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);

			YGE_CORE_INFO("Initializing GLFW");
			int success = glfwInit();
			YGE_CORE_ASSERT(success, "Coult not initialize GLFW!");

			glfwSetErrorCallback(WindowsWindow::GLFWErrorCallback);

			int monitorCount;
			GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
			for (int i = 0; i < monitorCount; i++) {
				WindowsPhysicalScreen* winScreen = new WindowsPhysicalScreen(i, monitors[i]);
				PhysicalScreen::s_Screens.push_back(winScreen);
				ScreenConnectedEvent event(*winScreen);
				PhysicalScreen::EventCallback(event);
			}

			glfwSetMonitorCallback([](GLFWmonitor* monitor, int event) {
				PhysicalScreen scr;
				if (event == GLFW_CONNECTED) {
					PhysicalScreen::s_Screens.clear();
					int monitorCount;
					GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
					for (int i = 0; i < monitorCount; i++) {
						WindowsPhysicalScreen* winScreen = new WindowsPhysicalScreen(i, monitors[i]);
						PhysicalScreen::s_Screens.push_back(winScreen);
						if (winScreen->m_Monitor == monitor) {
							scr = *winScreen;
						}
					}
					ScreenConnectedEvent event(scr);
					PhysicalScreen::EventCallback(event);
				}
				else if (event == GLFW_DISCONNECTED) {
					for (auto it = PhysicalScreen::s_Screens.begin();
						it != PhysicalScreen::s_Screens.end(); it++) {
						WindowsPhysicalScreen& winScreen = *static_cast<WindowsPhysicalScreen*>(*it);
						if (winScreen.m_Monitor == monitor) {
							scr = **it;
							PhysicalScreen::s_Screens.erase(it);
						}
					}
					ScreenDisconnectedEvent event(scr);
					PhysicalScreen::EventCallback(event);
				}
			});
		}

		if (m_Data.Decorated)
			glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		else
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::Renderer::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				#ifdef YGE_DEBUG
					glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
				#endif
				break;
		}

		if (m_Data.Fullscreen) {
			PhysicalScreen* screen = nullptr;
			if ((m_Data.MonitorPreference == -1) || 
				(m_Data.MonitorPreference >= PhysicalScreen::s_Screens.size())) {
				for (PhysicalScreen* scr : PhysicalScreen::s_Screens) {
					if (scr->IsPrimary()) {
						screen = scr;
						break;
					}
				}
			}
			else
				screen = PhysicalScreen::s_Screens.at(m_Data.MonitorPreference);

			if (screen == nullptr) {
				YGE_CORE_FATAL("Could not find any monitors!");
				return;
			}

			WindowsPhysicalScreen& winScreen = *static_cast<WindowsPhysicalScreen*>(screen);
			GLFWmonitor* monitor = winScreen.m_Monitor;
			int width = static_cast<int>(winScreen.m_Width);
			int height = static_cast<int>(winScreen.m_Height);
			int rbits = winScreen.m_RedBits;
			int gbits = winScreen.m_GreenBits;
			int bbits = winScreen.m_BlueBits;
			int refresh = static_cast<int>(winScreen.m_RefreshRate);
			
			glfwWindowHint(GLFW_RED_BITS, rbits);
			glfwWindowHint(GLFW_GREEN_BITS, gbits);
			glfwWindowHint(GLFW_BLUE_BITS, bbits);
			glfwWindowHint(GLFW_REFRESH_RATE, refresh);
			
			YGE_CORE_INFO("Creating fullscreen window - {0} ({1}, {2}){3}Hz", m_Data.Title, width, height, refresh);

			m_Window = glfwCreateWindow(width, height, m_Data.Title.c_str(), monitor, nullptr);
		}
		else {
			YGE_CORE_INFO("Creating window - {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

			m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
		}

		s_GLFWWindowCount++;

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ASSERT(false, CoreError::Renderer::YGE_NONE_RENDERER_API);
				RendererAPI::SetAPI(RendererAPI::API::OpenGL);
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				m_Data.API = RendererAPI::API::OpenGL;
				m_Context = new OpenGLContext(m_Window);
				break;
		}

		m_Context->Init();

		if (glfwRawMouseMotionSupported()) {
			YGE_CORE_DEBUG_INFO("Raw mouse input is supported. Enabling raw mouse motion.");
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		else {
			YGE_CORE_DEBUG_INFO("Raw mouse input is not supported.");
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);

		if (m_Data.Resizable)
			glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, GLFW_TRUE);
		else
			glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, GLFW_FALSE);
		
		if (m_Data.VSync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		if (specification.StartMaximized)
			Maximize();
		else
			Center();

		// GLFW callbacks

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int posx, int posy) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.PosX = posx;
			data.PosY = posy;
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			uint32_t w = static_cast<uint32_t>(width);
			uint32_t h = static_cast<uint32_t>(height);

			data.Width = w;
			data.Height = h;

			WindowResizedEvent event(w, h);
			data.EventCallback(event);
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			
			if (focused) {
				WindowFocusEvent event;
				data.EventCallback(event);
			}
			else {
				WindowLostFocusEvent event;
				data.EventCallback(event);
			}
		});

		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconified) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			if (iconified == GLFW_TRUE) {
				WindowLostFocusEvent event;
				data.EventCallback(event);
			}
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action) {
				case GLFW_PRESS: {
					KeyCode keycode = static_cast<KeyCode>(key);
					Input::OnKeyPressed(keycode);
					KeyPressedEvent event(keycode, false);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyCode keycode = static_cast<KeyCode>(key);
					Input::OnKeyReleased(keycode);
					KeyReleasedEvent event(keycode);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(static_cast<KeyCode>(key), true);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			KeyTypedEvent event(static_cast<KeyCode>( key));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action) {
				case GLFW_PRESS: {
					MouseButton mousebutton = static_cast<MouseButton>(button);
					Input::OnMouseButtonPressed(mousebutton);
					MouseButtonPressedEvent event(mousebutton);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButton mousebutton = static_cast<MouseButton>(button);
					Input::OnMouseButtonReleased(mousebutton);
					MouseButtonReleasedEvent event(mousebutton);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPosition, double yPosition) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			float x = static_cast<float>(xPosition), y = static_cast<float>(yPosition);
			Input::OnMouseMoved(x, y);
			MouseMovedEvent event(x, y);
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		// Make sure window position & size is still correct
		{
			glfwGetWindowPos(m_Window, &m_Data.PosX, &m_Data.PosY);
			int width, height;
			glfwGetWindowSize(m_Window, &width, &height);
			m_Data.Width = static_cast<uint32_t>(width);
			m_Data.Height = static_cast<uint32_t>(height);
		}

	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
		s_GLFWWindowCount--;
		if (!s_GLFWWindowCount) {
			YGE_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void WindowsWindow::GLFWErrorCallback(int error, const char* description) {
		YGE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void WindowsWindow::ProcessEvents() {
		glfwPollEvents();
	}

	void WindowsWindow::SwapBuffers() {
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetTitle(const std::string& title) {
		glfwSetWindowTitle(m_Window, title.c_str());
		m_Data.Title = title;
	}

	void WindowsWindow::SetPosition(const glm::vec2& position) {
		int x = static_cast<int>(position.x);
		int y = static_cast<int>(position.y);
		glfwSetWindowPos(m_Window, x, y);
		m_Data.PosX = x;
		m_Data.PosY = y;
	}

	void WindowsWindow::SetSize(const glm::vec2& size) {
		glfwSetWindowSize(m_Window, static_cast<int>(size.x), static_cast<int>(size.y));
		m_Data.Width = static_cast<uint32_t>(size.x);
		m_Data.Height = static_cast<uint32_t>(size.y);
	}

	void WindowsWindow::SetFullscreen(bool fullscreen) {
		if (fullscreen) {
			PhysicalScreen* screen = nullptr;
			if ((m_Data.MonitorPreference == -1) ||
				(m_Data.MonitorPreference >= PhysicalScreen::s_Screens.size())) {
				for (PhysicalScreen* scr : PhysicalScreen::s_Screens) {
					if (scr->IsPrimary()) {
						screen = scr;
						break;
					}
				}
			}
			else
				screen = PhysicalScreen::s_Screens.at(m_Data.MonitorPreference);

			if (screen == nullptr) {
				YGE_CORE_FATAL("Could not find any monitors!");
				return;
			}

			WindowsPhysicalScreen& winScreen = *static_cast<WindowsPhysicalScreen*>(screen);
			GLFWmonitor* monitor = winScreen.m_Monitor;
			int width = static_cast<int>(winScreen.m_Width);
			int height = static_cast<int>(winScreen.m_Height);
			int refresh = static_cast<int>(winScreen.m_RefreshRate);

			glfwSetWindowMonitor(m_Window, monitor, 0, 0, width, height, refresh);
			
			m_Data.Width = static_cast<uint32_t>(width);
			m_Data.Height = static_cast<uint32_t>(height);

		}
		else {
			glfwSetWindowMonitor(m_Window, nullptr, 0, 0, m_Data.Width, m_Data.Height, 0);
			Center();
		}
		m_Data.Fullscreen = fullscreen;
	}

	void WindowsWindow::SetResizable(bool resizable) {
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
		m_Data.Resizable = resizable;
	}

	bool WindowsWindow::IsIconified() const {
		return glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED) == GLFW_TRUE;
	}

	bool WindowsWindow::IsMaximized() const {
		return glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED) == GLFW_TRUE;
	}

	void WindowsWindow::Iconify() {
		glfwIconifyWindow(m_Window);
	}

	void WindowsWindow::Restore() {
		glfwRestoreWindow(m_Window);
	}

	void WindowsWindow::Maximize() {
		glfwMaximizeWindow(m_Window);
	}

	void WindowsWindow::Center() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int x = (mode->width - static_cast<int>(m_Data.Width)) / 2;
		int y = (mode->height - static_cast<int>(m_Data.Height)) / 2;
		glfwSetWindowPos(m_Window, x, y);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

}