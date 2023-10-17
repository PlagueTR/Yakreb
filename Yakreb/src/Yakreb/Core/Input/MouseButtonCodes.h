#pragma once

#include "Yakreb/Core/Log.h"

//glfw3.h

namespace Yakreb {

	typedef enum class ButtonCode : uint16_t {

		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2

	} Button;

	constexpr const char* GetButtonName(const ButtonCode buttoncode) {
		switch (buttoncode) {
		case ButtonCode::Button0: return "LMB";
		case ButtonCode::Button1: return "RMB";
		case ButtonCode::Button2: return "MMB";
		case ButtonCode::Button3: return "MB4";
		case ButtonCode::Button4: return "MB5";
		case ButtonCode::Button5: return "MB6";
		case ButtonCode::Button6: return "MB7";
		case ButtonCode::Button7: return "MB8";
		}

		YGE_CORE_DEBUG_ERROR("Unknown keycode ()!", (int)buttoncode);
		return "";
	}

}
