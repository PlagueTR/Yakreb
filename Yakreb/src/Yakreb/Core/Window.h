#pragma once

#include "Yakreb/Core/Core.h"
#include "Yakreb/Events/Event.h"

namespace Yakreb {

	// Window Interface
	class Window {
		public:
			struct WindowProperties {
				std::string Title;
				uint32_t Width;
				uint32_t Height;

				WindowProperties(const std::string& title = "Yakreb Application", uint32_t width = 1280, uint32_t height = 720) : Title(title), Width(width), Height(height) {}
			};

			using EventCallbackFn = std::function<void(Event&)>;

			virtual ~Window() = default;

			virtual void OnUpdate() = 0;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;

			virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

			virtual void SetVSync(bool enabled) = 0;
			virtual bool IsVSync() const = 0;

			static Window* Create(const WindowProperties& properties = WindowProperties());

		protected:
			static bool s_GLFWInitialized;

	};

}