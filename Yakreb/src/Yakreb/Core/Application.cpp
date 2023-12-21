#include "yakrebpch.h"
#include "Yakreb/Core/Application.h"

#include "Yakreb/Core/Input/Input.h"
#include "Yakreb/Core/GameTimer.h"
#include "Yakreb/Core/GameTime.h"

#include "Yakreb/Renderer/Renderer.h"

namespace Yakreb {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name) {

		YGE_CORE_ASSERT(!s_Instance, "Multiple instances of Application can not be created!");
		s_Instance = this;

		PhysicalScreen::SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window = Window::Create(Window::WindowSpecification(name));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Input::Init();
		Input::SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = ImGuiLayer::Create("Core ImGui");
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
		while (m_Running) {

			m_Window->ProcessEvents();
			m_Window->SwapBuffers();
			Input::Update();

			GameTimer::UpdateGameTime();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			RenderImGui();

		}
	}

	void Application::RenderImGui() {
		m_ImGuiLayer->BeginRender();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->EndRender();
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}

}