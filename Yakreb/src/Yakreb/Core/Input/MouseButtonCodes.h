#pragma once

#include "Yakreb/Core/Log/Log.h"

//glfw3.h

namespace Yakreb {

	enum class MouseButton : uint8_t {
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		Left = Button0,
		Right = Button1,
		Middle = Button2
	};

	constexpr const char* GetMouseButtonName(const MouseButton buttoncode) {
		switch (buttoncode) {
			case MouseButton::Button0: return "LMB";
			case MouseButton::Button1: return "RMB";
			case MouseButton::Button2: return "MMB";
			case MouseButton::Button3: return "MB4";
			case MouseButton::Button4: return "MB5";
			case MouseButton::Button5: return "MB6";
			case MouseButton::Button6: return "MB7";
			case MouseButton::Button7: return "MB8";
		}

		YGE_CORE_DEBUG_WARN("Unknown MouseButton ({})!", static_cast<int>(buttoncode));
		return "";
	}

}
