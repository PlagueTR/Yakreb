#pragma once

#include "Yakreb/Core/Input/KeyCodes.h"
#include "Yakreb/Core/Input/MouseButtonCodes.h"

namespace Yakreb {

	class Input {
		public:
			static bool IsKeyPressed(Key key);
			static bool IsMouseButtonPressed(Button button);
	};

}