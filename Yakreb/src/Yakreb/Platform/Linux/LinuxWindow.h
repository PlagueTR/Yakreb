#pragma once

#include "Yakreb/Core/Window.h"
#include "Yakreb/Renderer/GraphicsContext.h"

#include "Yakreb/Renderer/Renderer.h"

struct GLFWwindow;

namespace Yakreb {

	class LinuxWindow : public Window {
		public:
			LinuxWindow(const WindowSpecification& specification);
			virtual ~LinuxWindow();

			virtual void ProcessEvents() override;
			virtual void SwapBuffers() override;

			inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

			virtual std::string GetTitle() const override { return m_Data.Title; }
			virtual void SetTitle(const std::string& title) override;

			inline virtual int GetXPosition() const override { return m_Data.PosX; }
			inline virtual int GetYPosition() const override { return m_Data.PosY; }
			virtual void SetPosition(const glm::vec2& position) override;
			inline virtual glm::vec2 GetPosition() const override { return { m_Data.PosX, m_Data.PosY }; }

			inline virtual uint32_t GetWidth() const override { return m_Data.Width; }
			inline virtual uint32_t GetHeight() const override { return m_Data.Height; }
			virtual void SetSize(const glm::vec2& size) override;
			inline virtual glm::vec2 GetSize() const override { return { m_Data.Width, m_Data.Height }; }

			virtual void SetFullscreen(bool fullscreen) override;
			virtual bool IsFullscreen() const override { return m_Data.Fullscreen; }

			virtual void SetResizable(bool resizable) override;
			virtual bool IsResizable() const override { return m_Data.Resizable; }

			virtual bool IsIconified() const override;
			virtual bool IsMaximized() const override;
			virtual void Iconify() override;
			virtual void Restore() override;
			virtual void Maximize() override;
			virtual void Center() override;

			virtual void SetVSync(bool enabled) override;
			virtual bool IsVSync() const override { return m_Data.VSync; }

			virtual inline void* GetNativeWindow() const override { return m_Window; }

		private:
			struct WindowData : public WindowSpecification {
				std::string Title;
				uint32_t Width, Height;

				int MonitorPreference;

				bool Decorated;

				bool Resizable;
				bool Fullscreen;
				bool StartMaximized;

				bool VSync;

				int PosX, PosY;

				RendererAPI::API API;

				EventCallbackFn EventCallback;
			};

			virtual void Init(const WindowSpecification& properties);
			virtual void Shutdown();

			static void GLFWErrorCallback(int error, const char* description);

			GLFWwindow* m_Window;
			GraphicsContext* m_Context;

			WindowData m_Data;

	};

}