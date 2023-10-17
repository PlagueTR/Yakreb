#include "yakrebpch.h"
#include "LinuxWindow.h"

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

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			YGE_CORE_ASSERT(success, "Coult not initialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

	}

	void LinuxWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void LinuxWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	// Doesn't work yet
	void LinuxWindow::SetVSync(bool enabled) {
		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

	bool LinuxWindow::IsVSync() const {
		return m_Data.VSync;
	}

}