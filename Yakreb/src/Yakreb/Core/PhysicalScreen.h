#pragma once

#include "Yakreb/Core/Core.h"
#include "Yakreb/Core/Events/Event.h"

namespace Yakreb {

	class PhysicalScreen {
		public:
			using EventCallbackFn = std::function<void(Event&)>;

			virtual ~PhysicalScreen() = default;

			uint8_t GetID() const { return m_ID; }

			std::string GetName() const { return m_Name; }

			int GetXPosition() const { return m_PosX; }
			int GetYPosition() const { return m_PosY; }
			glm::vec2 GetPosition() const { return { m_PosX, m_PosY }; }

			uint32_t GetWidth() const { return m_Width; }
			uint32_t GetHeight() const { return m_Height; }
			glm::vec2 GetResolution() const { return { m_Width, m_Height }; }

			uint16_t GetRefreshRate() const { return m_RefreshRate; }

			bool IsPrimary() const { return m_Primary; }

			glm::vec4 GetWorkArea() const { return m_WorkArea; }

			static const PhysicalScreen& GetScreen(int id) { return *s_Screens.at(id); }
			static uint8_t GetScreenCount() { return static_cast<uint8_t>(s_Screens.size()); }

			static void SetEventCallback(const EventCallbackFn& callback) { EventCallback = callback; }

		protected:
			uint8_t m_ID;
			std::string m_Name;

			int m_PosX, m_PosY;
			uint32_t m_Width, m_Height;
			uint16_t m_RefreshRate;

			bool m_Primary;

			glm::vec4 m_WorkArea;

			static std::vector<PhysicalScreen*> s_Screens;
			inline static EventCallbackFn EventCallback;

	};

}