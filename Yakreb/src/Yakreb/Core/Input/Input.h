#pragma once

#include "Yakreb/Core/Input/KeyCodes.h"
#include "Yakreb/Core/Input/MouseButtonCodes.h"

namespace Yakreb {

	class Input {
		public:
			inline static bool IsKeyPressed(Key key) { return s_Instance->IsKeyPressedImpl(key); }
			inline static bool IsMouseButtonPressed(Button button) { return s_Instance->IsMouseButtonPressed(button); }

		protected:
			inline virtual bool IsKeyPressedImpl(Key key) = 0;
			inline virtual bool IsMouseButtonPressedImpl(Button button) = 0;

			static Input* s_Instance;

	};

}