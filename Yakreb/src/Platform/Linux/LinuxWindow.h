#pragma once
#include "Yakreb/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	class LinuxWindow : public Window {
	public:
		LinuxWindow(const WindowProperties& properties);
		virtual ~LinuxWindow();

		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return m_Data.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		struct WindowData {
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		static void GLFWErrorCallback(int error, const char* description);

		GLFWwindow* m_Window;

		WindowData m_Data;

	};

}