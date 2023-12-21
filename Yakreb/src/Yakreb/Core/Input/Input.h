#pragma once

#include "Yakreb/Core/Input/KeyCodes.h"
#include "Yakreb/Core/Input/MouseButtonCodes.h"
#include "Yakreb/Core/Input/ControllerCodes.h"

#include "Yakreb/Core/Application.h"
#include "Yakreb/Core/Window.h"

namespace Yakreb {

	using KeyState = ButtonState;

	enum class CursorMode : uint8_t {
		Normal = 0,
		Hidden = 1,
		Locked = 2
	};

	class Input {
		public:
			using EventCallbackFn = std::function<void(Event&)>;

			static void Init() { s_Window = Application::Get().GetWindow().GetNativeWindow(); }
			static void Update();

			inline static void SetEventCallback(const EventCallbackFn& callback) { s_EventCallback = callback; }

			static bool IsKeyPressed(KeyCode key) {
				return s_KeyData.find(key) != s_KeyData.end() && s_KeyData[key].State == KeyState::Pressed;
			}
			static bool IsKeyHeld(KeyCode key) {
				return s_KeyData.find(key) != s_KeyData.end() && s_KeyData[key].State == KeyState::Held;
			}
			static bool IsKeyReleased(KeyCode key) {
				return s_KeyData.find(key) != s_KeyData.end() && s_KeyData[key].State == KeyState::Released;
			}
			static bool IsKeyDown(KeyCode key) {
				return s_KeyData.find(key) != s_KeyData.end() && s_KeyData[key].IsDown;
			}

			static bool IsMouseButtonPressed(MouseButton button) {
				return s_MouseButtonData.find(button) != s_MouseButtonData.end() && s_MouseButtonData[button].State == ButtonState::Pressed;
			}
			static bool IsMouseButtonHeld(MouseButton button) {
				return s_MouseButtonData.find(button) != s_MouseButtonData.end() && s_MouseButtonData[button].State == ButtonState::Held;
			}
			static bool IsMouseButtonReleased(MouseButton button) {
				return s_MouseButtonData.find(button) != s_MouseButtonData.end() && s_MouseButtonData[button].State == ButtonState::Released;
			}
			static bool IsMouseButtonDown(MouseButton button) {
				return s_MouseButtonData.find(button) != s_MouseButtonData.end() && s_MouseButtonData[button].IsDown;
			}

			static float GetMouseX() { return s_MousePosition.x; }
			static float GetMouseY() { return s_MousePosition.y; }
			static glm::vec2 GetMousePosition() { return s_MousePosition; }

			static void SetCursorMode(CursorMode mode);
			static CursorMode GetCursorMode() { return s_CursorMode; }

			static bool IsControllerPresent(int controllerID) {
				return s_Controllers.find(controllerID) != s_Controllers.end();
			}
			static std::vector<int> GetConnectedControllerIDs() {
				std::vector<int> ids;
				ids.reserve(s_Controllers.size());
				std::transform(s_Controllers.begin(), s_Controllers.end(), std::back_inserter(ids),
					[](const std::pair<int, Controller>& pair) { return pair.first; }
				);
				return ids;
			}
			static const Controller* GetController(int controllerID) {
				if (!IsControllerPresent(controllerID))
					return nullptr;
				return &s_Controllers.at(controllerID);
			}
			static std::string GetControllerName(int controllerID) {
				if (!IsControllerPresent(controllerID))
					return "";
				return s_Controllers.at(controllerID).Name;
			}
			static ControllerType GetControllerType(int controllerID) {
				if (!IsControllerPresent(controllerID))
					return ControllerType::None;
				return s_Controllers.at(controllerID).Type;
			}
			static bool GetControllerAsGamepad(int controllerID) {
				if (!IsControllerPresent(controllerID))
					return false;
				return s_Controllers.at(controllerID).UseAsGamePad;
			}
			static void SetControllerAsGamepad(int controllerID, bool useAsGamepad) {
				if (!IsControllerPresent(controllerID))
					return;
				if (s_Controllers.at(controllerID).Type == ControllerType::Unmapped)
					return;
				s_Controllers.at(controllerID).UseAsGamePad = useAsGamepad;
			}

			static bool IsControllerButtonPressed(int controllerID, int button) {
				if (!IsControllerPresent(controllerID))
					return false;
				Controller& controller = s_Controllers.at(controllerID);
				return controller.ButtonStates.find(button) != controller.ButtonStates.end() && controller.ButtonStates[button] == ButtonState::Pressed;
			}
			static bool IsControllerButtonHeld(int controllerID, int button) {
				if (!IsControllerPresent(controllerID))
					return false;
				Controller& controller = s_Controllers.at(controllerID);
				return controller.ButtonStates.find(button) != controller.ButtonStates.end() && controller.ButtonStates[button] == ButtonState::Held;
			}
			static bool IsControllerButtonReleased(int controllerID, int button) {
				if (!IsControllerPresent(controllerID))
					return false;
				Controller& controller = s_Controllers.at(controllerID);
				return controller.ButtonStates.find(button) != controller.ButtonStates.end() && controller.ButtonStates[button] == ButtonState::Released;
			}
			static bool IsControllerButtonDown(int controllerID, int button) {
				if (!IsControllerPresent(controllerID))
					return false;
				auto& controllerButtonData = s_ControllerButtonData.at(controllerID);
				return controllerButtonData.ButtonStates.find(button) != controllerButtonData.ButtonStates.end() && controllerButtonData.ButtonStates[button].IsDown;
			}

			static bool IsControllerButtonPressed(int controllerID, ControllerButton button) {
				if (!IsControllerPresent(controllerID))
					return false;
				Controller& controller = s_Controllers.at(controllerID);
				return controller.ButtonStates.find(static_cast<int>(button)) != controller.ButtonStates.end() && controller.ButtonStates[static_cast<int>(button)] == ButtonState::Pressed;
			}
			static bool IsControllerButtonHeld(int controllerID, ControllerButton button) {
				if (!IsControllerPresent(controllerID))
					return false;
				Controller& controller = s_Controllers.at(controllerID);
				return controller.ButtonStates.find(static_cast<int>(button)) != controller.ButtonStates.end() && controller.ButtonStates[static_cast<int>(button)] == ButtonState::Held;
			}
			static bool IsControllerButtonReleased(int controllerID, ControllerButton button) {
				if (!IsControllerPresent(controllerID))
					return false;
				Controller& controller = s_Controllers.at(controllerID);
				return controller.ButtonStates.find(static_cast<int>(button)) != controller.ButtonStates.end() && controller.ButtonStates[static_cast<int>(button)] == ButtonState::Released;
			}
			static bool IsControllerButtonDown(int controllerID, ControllerButton button) {
				if (!IsControllerPresent(controllerID))
					return false;
				auto& controllerButtonData = s_ControllerButtonData.at(controllerID);
				return controllerButtonData.ButtonStates.find(static_cast<int>(button)) != controllerButtonData.ButtonStates.end() && controllerButtonData.ButtonStates[static_cast<int>(button)].IsDown;
			}

			static float GetControllerAxis(int controllerID, int axis) {
				if (!IsControllerPresent(controllerID))
					return 0.0f;
				Controller& controller = s_Controllers.at(controllerID);
				if (controller.AxisStates.find(axis) == controller.AxisStates.end())
					return 0.0f;
				return controller.AxisStates.at(axis);
			}
			static HatState GetControllerHat(int controllerID, int hat) {
				if (!IsControllerPresent(controllerID))
					return HatState::None;
				Controller& controller = s_Controllers.at(controllerID);
				if (controller.HatStates.find(hat) == controller.HatStates.end())
					return HatState::None;
				return controller.HatStates.at(hat);
			}

			static float GetControllerAxis(int controllerID, ControllerAxis axis) {
				if (!IsControllerPresent(controllerID))
					return 0.0f;
				Controller& controller = s_Controllers.at(controllerID);
				if (controller.AxisStates.find(static_cast<int>(axis)) == controller.AxisStates.end())
					return 0.0f;
				return controller.AxisStates.at(static_cast<int>(axis));
			}

			static float GetControllerDeadzone(int controllerID, int axis) {
				if (!IsControllerPresent(controllerID))
					return 0.0f;
				Controller& controller = s_Controllers.at(controllerID);
				if (controller.AxisDeadZones.find(axis) == controller.AxisDeadZones.end())
					return 0.0f;
				return controller.AxisDeadZones.at(axis);
			}
			static void SetControllerDeadzone(int controllerID, int axis, float deadzone) {
				if (!IsControllerPresent(controllerID))
					return;
				Controller& controller = s_Controllers.at(controllerID);
				if (controller.AxisStates.find(axis) == controller.AxisStates.end())
					return;
				controller.AxisDeadZones[axis] = deadzone;
			}

			static float GetControllerDeadzone(int controllerID, ControllerAxis axis) {
				if (!IsControllerPresent(controllerID))
					return 0.0f;
				Controller& controller = s_Controllers.at(controllerID);
				if (controller.AxisDeadZones.find(static_cast<int>(axis)) == controller.AxisDeadZones.end())
					return 0.0f;
				return controller.AxisDeadZones.at(static_cast<int>(axis));
			}
			static void SetControllerDeadzone(int controllerID, ControllerAxis axis, float deadzone) {
				if (!IsControllerPresent(controllerID))
					return;
				Controller& controller = s_Controllers.at(controllerID);
				if (controller.AxisStates.find(static_cast<int>(axis)) == controller.AxisStates.end())
					return;
				controller.AxisDeadZones[static_cast<int>(axis)] = deadzone;
			}

			static const std::map<int, Controller>& GetControllers() { return s_Controllers; }

		protected:
			struct StateInternal {
				bool IsDown = false;
				bool WasDown = false;
			};

			struct KeyStateInternal : StateInternal {
				ButtonState State = ButtonState::None;
			};

			using MouseButtonStateInternal = KeyStateInternal;

			struct ControllerButtonStateInternal {
				std::map<int, StateInternal> ButtonStates;
			};

			static ControllerType GetControllerType(const char* vidpid) {
				for (const std::pair<ControllerType, const std::vector<const char*>>& pair : detail::Controller::controllerTypeMap) {
					const std::vector<const char*>& ids = pair.second;
					for (const char* id : ids) {
						int i;
						for (i = 0; i < 8; i++) {
							if (vidpid[i] != id[i])
								break;
						}
						if (i == 8) {
							return pair.first;
						}
					}
				}
				return ControllerType::Generic;
			}

			inline static void OnKeyPressed(KeyCode key) {
				KeyStateInternal& keyData = s_KeyData[key];
				keyData.IsDown = true;
			}
			inline static void OnKeyReleased(KeyCode key) {
				KeyStateInternal& keyData = s_KeyData[key];
				keyData.IsDown = false;
			}
			inline static void OnMouseButtonPressed(MouseButton button) {
				MouseButtonStateInternal& buttonData = s_MouseButtonData[button];
				buttonData.IsDown = true;
			}
			inline static void OnMouseButtonReleased(MouseButton button) {
				MouseButtonStateInternal& buttonData = s_MouseButtonData[button];
				buttonData.IsDown = false;
			}
			inline static void OnMouseMoved(float x, float y) {
				s_MousePosition.x = x;
				s_MousePosition.y = y;
			}

			static void* s_Window;

			static std::map<KeyCode, KeyStateInternal> s_KeyData;
			static std::map<MouseButton, MouseButtonStateInternal> s_MouseButtonData;
			static std::map<int, ControllerButtonStateInternal> s_ControllerButtonData;

			static std::map<int, Controller> s_Controllers;

			static EventCallbackFn s_EventCallback;

			static glm::vec2 s_MousePosition;
			static CursorMode s_CursorMode;

			#ifdef YGE_PLATFORM_WINDOWS
				friend class WindowsWindow;
			#elif defined(YGE_PLATFORM_LINUX)
				friend class LinuxWindow;
			#endif

	};

	namespace detail::Input {

		class Input {
			public:
				inline static char vidpid[9] = { '\0' };
		};

	}

}