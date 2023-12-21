#pragma once

#include "Yakreb/Core/Core.h"
#include "Yakreb/Core/Events/Event.h"

#include "Yakreb/Core/PhysicalScreen.h"

namespace Yakreb {

	// Window Interface
	class Window {
		public:
			struct WindowSpecification {
				std::string Title;
				uint32_t Width, Height;

				int MonitorPreference;

				bool Decorated;

				bool Resizable;
				bool Fullscreen;
				bool StartMaximized;

				bool VSync;

				WindowSpecification(const std::string& title = "Yakreb Application",
					uint32_t width = 1280, uint32_t height = 720,
					int monitorPreference = -1, bool decorated = true,
					bool resizable = false, bool fullscreen = false,
					bool startMaximized = false, bool vsync = true) :
					Title(title), Width(width), Height(height),
					MonitorPreference(monitorPreference),
					Decorated(decorated), Resizable(resizable),
					Fullscreen(fullscreen), StartMaximized(startMaximized),
					VSync(vsync) {}

			};

			using EventCallbackFn = std::function<void(Event&)>;

			virtual ~Window() = default;
			
			virtual void ProcessEvents() = 0;
			virtual void SwapBuffers() = 0;

			virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

			virtual void SetTitle(const std::string& title) = 0;
			virtual std::string GetTitle() const = 0;

			virtual int GetXPosition() const = 0;
			virtual int GetYPosition() const = 0;
			virtual void SetPosition(const glm::vec2& position) = 0;
			virtual glm::vec2 GetPosition() const = 0;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;
			virtual void SetSize(const glm::vec2& size) = 0;
			virtual glm::vec2 GetSize() const = 0;

			virtual void SetFullscreen(bool fullscreen) = 0;
			virtual bool IsFullscreen() const = 0;

			virtual void SetResizable(bool resizable) = 0;
			virtual bool IsResizable() const = 0;

			virtual bool IsIconified() const = 0;
			virtual bool IsMaximized() const = 0;
			virtual void Iconify() = 0;
			virtual void Restore() = 0;
			virtual void Maximize() = 0;
			virtual void Center() = 0;

			virtual void SetVSync(bool enabled) = 0;
			virtual bool IsVSync() const = 0;

			virtual void* GetNativeWindow() const = 0;

			static Scope<Window> Create(const WindowSpecification& specification = WindowSpecification());

		protected:
			static uint8_t s_GLFWWindowCount;

	};

}