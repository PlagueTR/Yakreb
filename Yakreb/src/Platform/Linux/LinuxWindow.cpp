#include "yakrebpch.h"
#include "LinuxWindow.h"

#include "Yakreb/Core/Events/ApplicationEvent.h"
#include "Yakreb/Core/Events/KeyEvent.h"
#include "Yakreb/Core/Events/MouseEvent.h"

#include "Yakreb/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	LinuxWindow::LinuxWindow(const WindowProperties& properties) {
		Init(properties);
	}

	LinuxWindow::~LinuxWindow() {
		Shutdown();
	}

	void LinuxWindow::Init(const WindowProperties& properties) {
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		YGE_CORE_INFO("Creating window - {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWWindowCount) {

			YGE_CORE_INFO("{}", "Initializing GLFW");
			int success = glfwInit();
			YGE_CORE_ASSERT(success, "Coult not initialize GLFW!");

			glfwSetErrorCallback(LinuxWindow::GLFWErrorCallback);
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		s_GLFWWindowCount++;
		glfwMakeContextCurrent(m_Window);

		switch (RendererAPI::GetAPI()) {
			default:
				YGE_CORE_ERROR("{}", "Renderer API was set to None, defaulting to OpenGL");
				[[fallthrough]];
			case RendererAPI::API::OpenGL:
				m_Data.API = RendererAPI::API::OpenGL;
				m_Context = new OpenGLContext(m_Window);
				break;
		}

		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW callbacks

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = (uint32_t)width;
			data.Height = (uint32_t)height;

			WindowResizeEvent event((uint32_t)width, (uint32_t)height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(static_cast<KeyCode>(key));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(static_cast<ButtonCode>(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(static_cast<ButtonCode>(button));
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPosition, double yPosition) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPosition, (float)yPosition);
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

	}

	void LinuxWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
		s_GLFWWindowCount--;
		if (!s_GLFWWindowCount) {
			YGE_CORE_INFO("{}", "Terminating GLFW");
			glfwTerminate();
		}
	}

	void LinuxWindow::GLFWErrorCallback(int error, const char* description) {
		YGE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void LinuxWindow::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void LinuxWindow::SetVSync(bool enabled) {
		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

	bool LinuxWindow::IsVSync() const {
		return m_Data.VSync;
	}

}