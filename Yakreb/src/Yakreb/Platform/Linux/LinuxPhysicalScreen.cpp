#include "yakrebpch.h"
#include "LinuxPhysicalScreen.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	std::vector<PhysicalScreen*> PhysicalScreen::s_Screens;

	LinuxPhysicalScreen::LinuxPhysicalScreen(int id, GLFWmonitor* monitor) {
		m_ID = static_cast<uint8_t>(id);
		m_Monitor = monitor;
		m_Primary = monitor == glfwGetPrimaryMonitor();
		Init();
	}

	void LinuxPhysicalScreen::Init() {
		m_Name = glfwGetMonitorName(m_Monitor);
		glfwGetMonitorPos(m_Monitor, &m_PosX, &m_PosY);
		const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);
		m_Width = static_cast<uint32_t>(mode->width);
		m_Height = static_cast<uint32_t>(mode->height);
		m_RefreshRate = static_cast<uint16_t>(mode->refreshRate);
		m_RedBits = mode->redBits;
		m_GreenBits = mode->greenBits;
		m_BlueBits = mode->blueBits;
		int tlx, tly, w, h;
		glfwGetMonitorWorkarea(m_Monitor, &tlx, &tly, &w, &h);
		m_WorkArea = glm::vec4(tlx, tly, tlx + w, tly + h);
	}

}