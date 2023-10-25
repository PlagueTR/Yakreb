#pragma once

#include "Yakreb/Core/Input/KeyCodes.h"
#include "Yakreb/Core/Input/MouseButtonCodes.h"

namespace Yakreb {

	class Input {
		public:
			inline static bool IsKeyPressed(Key key) { return s_Instance->IsKeyPressedImpl(key); }
			inline static bool IsMouseButtonPressed(Button button) { return s_Instance->IsMouseButtonPressedImpl(button); }

			inline static glm::vec2 GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

		protected:
			inline virtual bool IsKeyPressedImpl(Key key) = 0;
			inline virtual bool IsMouseButtonPressedImpl(Button button) = 0;

			inline virtual glm::vec2 GetMousePositionImpl() = 0;

			static Input* s_Instance;

	};

}