#pragma once

#include "Yakreb/Core/Log/Log.h"

//glfw3.h

namespace Yakreb {

	typedef enum class KeyCode : uint16_t {
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348,

		Unknown = std::numeric_limits<uint16_t>::max()
	} Key;

	namespace detail::KeyCodes {
		class Input {
			public:
				inline static char unicodeBuffer[5] = { '\0' };
		};
	}

	static const char* GetUTF8(const unsigned int unicode) {
		std::memset(detail::KeyCodes::Input::unicodeBuffer, '\0', 5);
		if (unicode <= 0x7F) {
			detail::KeyCodes::Input::unicodeBuffer[0] = unicode;
		}
		else if (unicode <= 0x7FF) {
			detail::KeyCodes::Input::unicodeBuffer[0] = (unicode >> 6) + 192;
			detail::KeyCodes::Input::unicodeBuffer[1] = (unicode & 63) + 128;
		}
		else if (0xd800 <= unicode && unicode <= 0xdfff) {} // Invalid block of utf8
		else if (unicode <= 0xFFFF) {
			detail::KeyCodes::Input::unicodeBuffer[0] = (unicode >> 12) + 224;
			detail::KeyCodes::Input::unicodeBuffer[1] = ((unicode >> 6) & 63) + 128;
			detail::KeyCodes::Input::unicodeBuffer[2] = (unicode & 63) + 128;
		}
		else if (unicode <= 0x10FFFF) {
			detail::KeyCodes::Input::unicodeBuffer[0] = (unicode >> 18) + 240;
			detail::KeyCodes::Input::unicodeBuffer[1] = ((unicode >> 12) & 63) + 128;
			detail::KeyCodes::Input::unicodeBuffer[2] = ((unicode >> 6) & 63) + 128;
			detail::KeyCodes::Input::unicodeBuffer[3] = (unicode & 63) + 128;
		}
		return detail::KeyCodes::Input::unicodeBuffer;
	}

	constexpr const char* GetKeyName(const KeyCode keycode) {
		switch (keycode)
		{
			case KeyCode::Space:			return "Space";
			case KeyCode::Apostrophe:		return "'";
			case KeyCode::Comma:			return ",";
			case KeyCode::Minus:			return "-";
			case KeyCode::Period:			return ".";
			case KeyCode::Slash:			return "/";

			case KeyCode::D0:				return "0";
			case KeyCode::D1:				return "1";
			case KeyCode::D2:				return "2";
			case KeyCode::D3:				return "3";
			case KeyCode::D4:				return "4";
			case KeyCode::D5:				return "5";
			case KeyCode::D6:				return "6";
			case KeyCode::D7:				return "7";
			case KeyCode::D8:				return "8";
			case KeyCode::D9:				return "9";

			case KeyCode::Semicolon:		return ";";
			case KeyCode::Equal:			return "=";

			case KeyCode::A:				return "A";
			case KeyCode::B:				return "B";
			case KeyCode::C:				return "C";
			case KeyCode::D:				return "D";
			case KeyCode::E:				return "E";
			case KeyCode::F:				return "F";
			case KeyCode::G:				return "G";
			case KeyCode::H:				return "H";
			case KeyCode::I:				return "I";
			case KeyCode::J:				return "J";
			case KeyCode::K:				return "K";
			case KeyCode::L:				return "L";
			case KeyCode::M:				return "M";
			case KeyCode::N:				return "N";
			case KeyCode::O:				return "O";
			case KeyCode::P:				return "P";
			case KeyCode::Q:				return "Q";
			case KeyCode::R:				return "R";
			case KeyCode::S:				return "S";
			case KeyCode::T:				return "T";
			case KeyCode::U:				return "U";
			case KeyCode::V:				return "V";
			case KeyCode::W:				return "W";
			case KeyCode::X:				return "X";
			case KeyCode::Y:				return "Y";
			case KeyCode::Z:				return "Z";

			case KeyCode::LeftBracket:		return "[";
			case KeyCode::Backslash:		return "\\";
			case KeyCode::RightBracket:		return "]";
			case KeyCode::GraveAccent:		return "`";

			case KeyCode::World1:			return "NON US #1";
			case KeyCode::World2:			return "NON US #2";

			case KeyCode::Escape:			return "Esc";
			case KeyCode::Enter:			return "Enter";
			case KeyCode::Tab:				return "Tab";
			case KeyCode::Backspace:		return "Backspace";
			case KeyCode::Insert:			return "Insert";
			case KeyCode::Delete:			return "Delete";
			case KeyCode::Right:			return "Right";
			case KeyCode::Left:				return "Left";
			case KeyCode::Down:				return "Down";
			case KeyCode::Up:				return "Up";
			case KeyCode::PageUp:			return "Page up";
			case KeyCode::PageDown:			return "Page down";
			case KeyCode::Home:				return "Home";
			case KeyCode::End:				return "End";
			case KeyCode::CapsLock:			return "Caps lock";
			case KeyCode::ScrollLock:		return "Scroll lock";
			case KeyCode::NumLock:			return "Num lock";
			case KeyCode::PrintScreen:		return "Print screen";
			case KeyCode::Pause:			return "Pause";
			case KeyCode::F1:				return "F1";
			case KeyCode::F2:				return "F2";
			case KeyCode::F3:				return "F3";
			case KeyCode::F4:				return "F4";
			case KeyCode::F5:				return "F5";
			case KeyCode::F6:				return "F6";
			case KeyCode::F7:				return "F7";
			case KeyCode::F8:				return "F8";
			case KeyCode::F9:				return "F9";
			case KeyCode::F10:				return "F10";
			case KeyCode::F11:				return "F11";
			case KeyCode::F12:				return "F12";
			case KeyCode::F13:				return "F13";
			case KeyCode::F14:				return "F14";
			case KeyCode::F15:				return "F15";
			case KeyCode::F16:				return "F16";
			case KeyCode::F17:				return "F17";
			case KeyCode::F18:				return "F18";
			case KeyCode::F19:				return "F19";
			case KeyCode::F20:				return "F20";
			case KeyCode::F21:				return "F21";
			case KeyCode::F22:				return "F22";
			case KeyCode::F23:				return "F23";
			case KeyCode::F24:				return "F24";
			case KeyCode::F25:				return "F25";

			case KeyCode::KP0:				return "Num 0";
			case KeyCode::KP1:				return "Num 1";
			case KeyCode::KP2:				return "Num 2";
			case KeyCode::KP3:				return "Num 3";
			case KeyCode::KP4:				return "Num 4";
			case KeyCode::KP5:				return "Num 5";
			case KeyCode::KP6:				return "Num 6";
			case KeyCode::KP7:				return "Num 7";
			case KeyCode::KP8:				return "Num 8";
			case KeyCode::KP9:				return "Num 9";
			case KeyCode::KPDecimal:		return "Num .";
			case KeyCode::KPDivide:			return "Num /";
			case KeyCode::KPMultiply:		return "Num *";
			case KeyCode::KPSubtract:		return "Num -";
			case KeyCode::KPAdd:			return "Num +";
			case KeyCode::KPEnter:			return "Num enter";
			case KeyCode::KPEqual:			return "Num =";

			case KeyCode::LeftShift:		return "Left shift";
			case KeyCode::LeftControl:		return "Left ctrl";
			case KeyCode::LeftAlt:			return "Left alt";
			case KeyCode::LeftSuper:		return "Left super";
			case KeyCode::RightShift:		return "Right shift";
			case KeyCode::RightControl:		return "Right ctrl";
			case KeyCode::RightAlt:			return "Right alt";
			case KeyCode::RightSuper:		return "Right super";
			case KeyCode::Menu:				return "Menu";
		}

		YGE_CORE_DEBUG_WARN("Unknown KeyCode ({})!", static_cast<int>(keycode));
		return "";
	}

}