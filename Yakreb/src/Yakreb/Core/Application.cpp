#include "yakrebpch.h"
#include "Yakreb/Core/Application.h"

#include "Yakreb/Core/Input/Input.h"
#include "Yakreb/Core/GameTimer.h"
#include "Yakreb/Core/GameTime.h"

#include <glad/glad.h>

namespace Yakreb {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string &name) {

		YGE_CORE_ASSERT(!s_Instance, "Multiple instances of Application can not be created!");
		s_Instance = this;

		m_Window = Window::Create(Window::WindowProperties(name));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer("Core ImGui");
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& event) {
		YGE_CORE_DEBUG_TRACE("{}", event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (event.Handled)
				break;
			(*it)->OnEvent(event);
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer) {
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer* overlay) {
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	void Application::Run() {

		int state = 0;
		float frac = 0.0f;
		float speed = 1.0f;

		float r, g, b;

		while (m_Running) {

			m_Window->OnUpdate();

			GameTimer::UpdateGameTime();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->BeginRender();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			// Other rendering
			{
				frac += speed * GameTime::GetScaledDeltaTime();
				if (frac > 1.0f) { frac -= 1.0f; state++; };

				switch (state) {
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
				case 6:
					r = 1.0f;
					g = frac;
					b = 0.0f;
					state = 0;
				}

				glClearColor(r, g, b, 1);
				glClear(GL_COLOR_BUFFER_BIT);
			}

			m_ImGuiLayer->EndRender();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}

}