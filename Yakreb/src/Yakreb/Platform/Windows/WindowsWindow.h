#pragma once

#include "Yakreb/Core/Window.h"
#include "Yakreb/Renderer/GraphicsContext.h"

#include "Yakreb/Renderer/RendererAPI.h"

struct GLFWwindow;

namespace Yakreb {

	class WindowsWindow : public Window {
		public:
			WindowsWindow(const WindowProperties& properties);
			virtual ~WindowsWindow();

			virtual void OnUpdate() override;

			inline virtual uint32_t GetWidth() const override { return m_Data.Width; }
			inline virtual uint32_t GetHeight() const override { return m_Data.Height; }

			inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

			void SetVSync(bool enabled) override;
			bool IsVSync() const override;

			inline void* GetNativeWindow() const override { return m_Window; }

		private:
			struct WindowData {
				std::string Title;
				uint32_t Width, Height;
				RendererAPI::API API;

				bool VSync;

				EventCallbackFn EventCallback;
			};

			virtual void Init(const WindowProperties& properties);
			virtual void Shutdown();

			static void GLFWErrorCallback(int error, const char* description);

			GLFWwindow* m_Window;
			GraphicsContext* m_Context;

			WindowData m_Data;

	};

}