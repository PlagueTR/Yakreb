#pragma once

#include "Yakreb/Core/Input/KeyCodes.h"
#include "Yakreb/Core/Input/MouseButtonCodes.h"

namespace Yakreb {

	class Input {
		public:
			static void Init();

			static bool IsKeyPressed(Key key);
			static bool IsMouseButtonPressed(Button button);

			static glm::vec2 GetMousePosition();

		private:
			static void* s_NativeWindow;

	};

}