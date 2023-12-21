#pragma once

#include "Yakreb/Core/Log/Log.h"

#include "Yakreb/Core/Input/Controller.h"

//glfw3.h

namespace Yakreb {

	enum class ControllerButton : uint8_t {
		South = 0,
		East = 1,
		West = 2,
		North = 3,
		LeftBumper = 4,
		RightBumper = 5,
		Back = 6,
		Start = 7,
		Guide = 8,
		LeftThumb = 9,
		RightThumb = 10,
		DPadUp = 11,
		DPadRight = 12,
		DPadDown = 13,
		DPadLeft = 14,

        LeftStick = LeftThumb,
        RightStick = RightThumb,

		// Xbox
		A = South,
		B = East,
		X = West,
		Y = North,

		// PlayStation
		Cross = South,
		Circle = East,
		Square = West,
		Triangle = North
	};

	enum class ControllerAxis : uint8_t {
		LeftX = 0,
		LeftY = 1,
		RightX = 2,
		RightY = 3,
		LeftTrigger = 4,
		RightTrigger = 5
	};

    constexpr const char* GetControllerTypeName(const ControllerType controllerType) {
        switch (controllerType) {
            case ControllerType::None:              return "None";
            case ControllerType::Unmapped:          return "Unmapped";
            case ControllerType::Generic:           return "Generic";
            case ControllerType::Apple:             return "Apple";
            case ControllerType::AstroCity:         return "Astro City";
            case ControllerType::Dreamcast:         return "Dreamcast";
            case ControllerType::EightBitDo:        return "8BitDo";
            case ControllerType::GameCube:          return "GameCube";
            case ControllerType::Luna:              return "Luna";
            case ControllerType::MobileTouch:       return "Mobile Touch";
            case ControllerType::N64:               return "N64";
            case ControllerType::NeoGeo:            return "Neo Geo";
            case ControllerType::Ouya:              return "Ouya";
            case ControllerType::PCEngine:          return "PC Engine";
            case ControllerType::PlayStation1:      return "PlayStation 1";
            case ControllerType::PlayStation3:      return "PlayStation 3";
            case ControllerType::PlayStation4:      return "PlayStation 4";
            case ControllerType::PlayStation5:      return "PlayStation 5";
            case ControllerType::SNES:              return "SNES";
            case ControllerType::Saturn:            return "Saturn";
            case ControllerType::Stadia:            return "Stadia";
            case ControllerType::Steam:             return "Steam";
            case ControllerType::SteamV2:           return "SteamV2";
            case ControllerType::SuperFamicom:      return "Super Famicom";
            case ControllerType::Switch:            return "Switch";
            case ControllerType::SwitchJoyConLeft:  return "Switch JoyCon Left";
            case ControllerType::SwitchJoyConRight: return "Switch JoyCon Right";
            case ControllerType::SwitchLike:        return "Switch-Like";
            case ControllerType::SwitchPro:         return "Switch Pro";
            case ControllerType::WiiRemote:         return "Wii Remote";
            case ControllerType::XBox360:           return "XBox 360";
            case ControllerType::XBoxLike:          return "XBox-Like";
            case ControllerType::XBoxOne:           return "XBox One";
        }

        YGE_CORE_DEBUG_WARN("Unknown ControllerType ({})!", static_cast<int>(controllerType));
        return "";
    }

    constexpr const char* GetGenericButtonName(const ControllerButton buttoncode) {
        switch (buttoncode) {
            case ControllerButton::DPadUp:    return "Up";
            case ControllerButton::DPadDown:  return "Down";
            case ControllerButton::DPadLeft:  return "Left";
            case ControllerButton::DPadRight: return "Right";
            case ControllerButton::South:       return "South";
            case ControllerButton::East:        return "East";
            case ControllerButton::Back:        return "Back";
            case ControllerButton::Guide:       return "Guide";
            case ControllerButton::LeftBumper:  return "LeftBumper";
            case ControllerButton::LeftThumb:   return "LeftThumb";
            case ControllerButton::RightBumper: return "RightBumper";
            case ControllerButton::RightThumb:  return "RightThumb";
            case ControllerButton::Start:       return "Start";
            case ControllerButton::West:        return "West";
            case ControllerButton::North:       return "North";
        }

        YGE_CORE_DEBUG_WARN("Unknown ControllerButton ({})!", static_cast<int>(buttoncode));
        return "";
    }

    // Data taken from https://github.com/offalynne/Input/blob/dev_4.2_LTS/datafiles/buttonlabels.csv
	constexpr const char* GetButtonName(const ControllerType controllerType, const ControllerButton buttoncode) {
        switch (buttoncode) {
            case ControllerButton::DPadUp:    return "Up";
            case ControllerButton::DPadDown:  return "Down";
            case ControllerButton::DPadLeft:  return "Left";
            case ControllerButton::DPadRight: return "Right";
        }
        switch (controllerType) {
            case ControllerType::None:
            case ControllerType::Unmapped:
            case ControllerType::Generic:
                YGE_CORE_DEBUG_WARN("ControllerType {}!", GetControllerTypeName(controllerType));
                return "";
            case ControllerType::Apple:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Options";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L1";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "R1";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Menu";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::AstroCity:
                switch (buttoncode) {
                    case ControllerButton::South:       return "D";
                    case ControllerButton::East:        return "E";
                    case ControllerButton::Back:        return "Credit";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "C";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "A";
                    case ControllerButton::North:       return "B";
                }
                break;
            case ControllerType::Dreamcast:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::EightBitDo:
                switch (buttoncode) {
                    case ControllerButton::South:       return "B";
                    case ControllerButton::East:        return "A";
                    case ControllerButton::Back:        return "Select";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "R";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "Y";
                    case ControllerButton::North:       return "X";
                }
                break;
            case ControllerType::GameCube:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "X";
                    case ControllerButton::Back:        return "";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "Z";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "B";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::Luna:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Action";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "LB";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "RB";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Menu";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::MobileTouch:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Back";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "LB";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "RB";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::N64:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "R";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "";
                    case ControllerButton::North:       return "";
                }
                break;
            case ControllerType::NeoGeo:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Select";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "C";
                    case ControllerButton::North:       return "D";
                }
                break;
            case ControllerType::Ouya:
                switch (buttoncode) {
                    case ControllerButton::South:       return "O";
                    case ControllerButton::East:        return "A";
                    case ControllerButton::Back:        return "";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "LB";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "RB";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "U";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::PCEngine:
                switch (buttoncode) {
                    case ControllerButton::South:       return "II";
                    case ControllerButton::East:        return "I";
                    case ControllerButton::Back:        return "Select";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Run";
                    case ControllerButton::West:        return "";
                    case ControllerButton::North:       return "";
                }
                break;
            case ControllerType::PlayStation1:
            case ControllerType::PlayStation3:
                switch (buttoncode) {
                    case ControllerButton::South:       return "Cross";
                    case ControllerButton::East:        return "Circle";
                    case ControllerButton::Back:        return "Select";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L1";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "R1";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "Square";
                    case ControllerButton::North:       return "Triangle";
                }
                break;
            case ControllerType::PlayStation4:
                switch (buttoncode) {
                    case ControllerButton::South:       return "Cross";
                    case ControllerButton::East:        return "Circle";
                    case ControllerButton::Back:        return "Share";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L1";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "R1";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Options";
                    case ControllerButton::West:        return "Square";
                    case ControllerButton::North:       return "Triangle";
                }
                break;
            case ControllerType::PlayStation5:
                switch (buttoncode) {
                    case ControllerButton::South:       return "Cross";
                    case ControllerButton::East:        return "Circle";
                    case ControllerButton::Back:        return "Create";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L1";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "R1";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Options";
                    case ControllerButton::West:        return "Square";
                    case ControllerButton::North:       return "Triangle";
                }
                break;
            case ControllerType::Saturn:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Select";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "Z";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::Stadia:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Options";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L1";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "R1";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Menu";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::Steam:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Back";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "LB";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "RB";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::SteamV2:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "View";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L1";
                    case ControllerButton::LeftThumb:   return "L3";
                    case ControllerButton::RightBumper: return "R1";
                    case ControllerButton::RightThumb:  return "R3";
                    case ControllerButton::Start:       return "Menu";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::SNES:
            case ControllerType::SuperFamicom:
                switch (buttoncode) {
                    case ControllerButton::South:       return "B";
                    case ControllerButton::East:        return "A";
                    case ControllerButton::Back:        return "Select";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "R";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "Y";
                    case ControllerButton::North:       return "X";
                }
                break;
            case ControllerType::SwitchJoyConLeft:
                switch (buttoncode) {
                    case ControllerButton::South:       return "";
                    case ControllerButton::East:        return "";
                    case ControllerButton::Back:        return "Capture";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "SL";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "SR";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "-";
                    case ControllerButton::West:        return "";
                    case ControllerButton::North:       return "";
                }
                break;
            case ControllerType::SwitchJoyConRight:
                switch (buttoncode) {
                    case ControllerButton::South:       return "";
                    case ControllerButton::East:        return "";
                    case ControllerButton::Back:        return "Home";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "SL";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "SR";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "+";
                    case ControllerButton::West:        return "";
                    case ControllerButton::North:       return "";
                }
                break;
            case ControllerType::Switch:
            case ControllerType::SwitchLike:
            case ControllerType::SwitchPro:
                switch (buttoncode) {
                    case ControllerButton::South:       return "B";
                    case ControllerButton::East:        return "A";
                    case ControllerButton::Back:        return "-";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "L";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "R";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "+";
                    case ControllerButton::West:        return "Y";
                    case ControllerButton::North:       return "X";
                }
                break;
            case ControllerType::WiiRemote:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "";
                    case ControllerButton::Guide:       return "Home";
                    case ControllerButton::LeftBumper:  return "-";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "+";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "";
                    case ControllerButton::West:        return "1";
                    case ControllerButton::North:       return "2";
                }
                break;
            case ControllerType::XBox360:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "Back";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "LB";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "RB";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Start";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            case ControllerType::XBoxLike:
            case ControllerType::XBoxOne:
                switch (buttoncode) {
                    case ControllerButton::South:       return "A";
                    case ControllerButton::East:        return "B";
                    case ControllerButton::Back:        return "View";
                    case ControllerButton::Guide:       return "";
                    case ControllerButton::LeftBumper:  return "LB";
                    case ControllerButton::LeftThumb:   return "";
                    case ControllerButton::RightBumper: return "RB";
                    case ControllerButton::RightThumb:  return "";
                    case ControllerButton::Start:       return "Menu";
                    case ControllerButton::West:        return "X";
                    case ControllerButton::North:       return "Y";
                }
                break;
            default:
                YGE_CORE_DEBUG_WARN("Unknown ControllerType ({})!", static_cast<int>(controllerType));
                return "";
        }

		YGE_CORE_DEBUG_WARN("Unknown ControllerButton ({})!", static_cast<int>(buttoncode));
		return "";
	}

    constexpr const char* GetGenericAxisName(const ControllerAxis axiscode) {
        switch (axiscode) {
            case ControllerAxis::LeftX:  return "Left Stick X";
            case ControllerAxis::LeftY:  return "Left Stick Y";
            case ControllerAxis::RightX: return "Right Stick X";
            case ControllerAxis::RightY: return "Right Stick Y";
            case ControllerAxis::LeftTrigger:  return "Left Trigger";
            case ControllerAxis::RightTrigger: return "Right Trigger";
        }

        YGE_CORE_DEBUG_WARN("Unknown ControllerAxis ({})!", static_cast<int>(axiscode));
        return "";
    }

    // Data taken from https://github.com/offalynne/Input/blob/dev_4.2_LTS/datafiles/buttonlabels.csv
	constexpr const char* GetAxisName(const ControllerType controllerType, const ControllerAxis axiscode) {
		switch (axiscode) {
            case ControllerAxis::LeftX:  return "Left Stick X";
			case ControllerAxis::LeftY:  return "Left Stick Y";
			case ControllerAxis::RightX: return "Right Stick X";
			case ControllerAxis::RightY: return "Right Stick Y";
		}
		switch (controllerType) {
            case ControllerType::None:
            case ControllerType::Unmapped:
            case ControllerType::Generic:
                YGE_CORE_DEBUG_WARN("ControllerType {}!", GetControllerTypeName(controllerType));
                return "";
            case ControllerType::AstroCity:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "";
                    case ControllerAxis::RightTrigger: return "F";
                }
                break;
            case ControllerType::Dreamcast:
            case ControllerType::GameCube:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "L";
                    case ControllerAxis::RightTrigger: return "R";
                }
                break;
            case ControllerType::N64:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "Z";
                    case ControllerAxis::RightTrigger: return "";
                }
                break;
            case ControllerType::Saturn:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "R";
                    case ControllerAxis::RightTrigger: return "C";
                }
                break;
            case ControllerType::WiiRemote:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "Z";
                    case ControllerAxis::RightTrigger: return "C";
                }
                break;
            case ControllerType::Apple:
            case ControllerType::EightBitDo:
            case ControllerType::PlayStation1:
            case ControllerType::PlayStation3:
            case ControllerType::PlayStation4:
            case ControllerType::PlayStation5:
            case ControllerType::Stadia:
            case ControllerType::SteamV2:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "L2";
                    case ControllerAxis::RightTrigger: return "R2";
                }
                break;
            case ControllerType::NeoGeo:
            case ControllerType::PCEngine:
            case ControllerType::SNES:
            case ControllerType::SuperFamicom:
            case ControllerType::SwitchJoyConLeft:
            case ControllerType::SwitchJoyConRight:
                return "";
            case ControllerType::Switch:
            case ControllerType::SwitchLike:
            case ControllerType::SwitchPro:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "ZL";
                    case ControllerAxis::RightTrigger: return "ZR";
                }
                break;
            case ControllerType::Luna:
            case ControllerType::MobileTouch:
            case ControllerType::Ouya:
            case ControllerType::Steam:
            case ControllerType::XBox360:
            case ControllerType::XBoxLike:
            case ControllerType::XBoxOne:
                switch (axiscode) {
                    case ControllerAxis::LeftTrigger:  return "LT";
                    case ControllerAxis::RightTrigger: return "RT";
                }
                break;
            default:
                YGE_CORE_DEBUG_WARN("Unknown ControllerType ({})!", static_cast<int>(controllerType));
                return "";
		}

		YGE_CORE_DEBUG_WARN("Unknown ControllerAxis ({})!", static_cast<int>(axiscode));
		return "";
	}

}