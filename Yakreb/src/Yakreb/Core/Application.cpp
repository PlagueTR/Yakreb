#include "yakrebpch.h"
#include "Yakreb/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {

		uint8_t state = 0;
		float frac = 0.0f;
		float speed = 1e-2f;

		float r, g, b;

		while (m_Running) {
			frac += speed;
			if (frac > 1.0f) { frac -= 1.0f; state++; }

			switch (state) {
				case 6:
					state = 0;
				case 0:
					r = 1.0f;
					g = frac;
					b = 0.0f;
					break;
				case 1:
					r = 1.0f - frac;
					g = 1.0f;
					b = 0.0f;
					break;
				case 2:
					r = 0.0f;
					g = 1.0f;
					b = frac;
					break;
				case 3:
					r = 0.0f;
					g = 1.0f - frac;
					b = 1.0f;
					break;
				case 4:
					r = frac;
					g = 0.0f;
					b = 1.0f;
					break;
				case 5:
					r = 1.0f;
					g = 0.0f;
					b = 1.0f - frac;
					break;
			}

			YGE_DEBUG_TRACE("rgb: {0:02X}{1:02X}{2:02X}", (int)(r * 255.0f), (int)(g * 255.0f), (int)(b * 255.0f));

			glClearColor(r, g, b, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}

}