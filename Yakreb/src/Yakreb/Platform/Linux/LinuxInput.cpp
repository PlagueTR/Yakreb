#include "yakrebpch.h"
#include "Yakreb/Core/Input/Input.h"

#include "Yakreb/Core/Events/ControllerEvent.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	void* Input::s_Window = nullptr;
	Input::EventCallbackFn Input::s_EventCallback;

	std::map<KeyCode, Input::KeyStateInternal> Input::s_KeyData;
	std::map<MouseButton, Input::MouseButtonStateInternal> Input::s_MouseButtonData;
	std::map<int, Input::ControllerButtonStateInternal> Input::s_ControllerButtonData;

	std::map<int, Controller> Input::s_Controllers;

	glm::vec2 Input::s_MousePosition = glm::vec2();
	CursorMode Input::s_CursorMode = CursorMode::Normal;

	void Input::Update() {

		GLFWwindow* GLFWwin = static_cast<GLFWwindow*>(s_Window);

		// Update controller states
		for (int id = GLFW_JOYSTICK_1; id < GLFW_JOYSTICK_LAST; id++) {
			if (glfwJoystickPresent(id) == GLFW_TRUE) {

				bool justConnected = s_Controllers.find(id) == s_Controllers.end();
				float defaultDeadzone = 0.2f;

				Controller& controller = s_Controllers[id];

				if (justConnected) {
					controller.ID = id;
					if (glfwJoystickIsGamepad(id) == GLFW_TRUE) {
						controller.UseAsGamePad = true;
						const char* guid = glfwGetJoystickGUID(id);
						std::memcpy(detail::Input::Input::vidpid, guid + 8, 4);
						std::memcpy(detail::Input::Input::vidpid + 4, guid + 16, 4);
						controller.Type = GetControllerType(detail::Input::Input::vidpid);
						controller.Name = glfwGetGamepadName(id);
					}
					else {
						controller.UseAsGamePad = false;
						controller.Type = ControllerType::Unmapped;
						controller.Name = glfwGetJoystickName(id);
					}
				}

				if (controller.UseAsGamePad) {
					GLFWgamepadstate gamepadstate;
					glfwGetGamepadState(id, &gamepadstate);
					std::map<int, StateInternal>& buttonStates = s_ControllerButtonData[id].ButtonStates;
					for (int i = 0; i < (sizeof(gamepadstate.buttons)/sizeof(unsigned char)); i++) {
						StateInternal& buttonState = buttonStates[i];
						buttonState.WasDown = buttonState.IsDown;
						buttonState.IsDown = (gamepadstate.buttons[i] == GLFW_PRESS);

						if (!buttonState.IsDown && !buttonState.WasDown)
							controller.ButtonStates[i] = ButtonState::None;
						else if (buttonState.IsDown && buttonState.WasDown)
							controller.ButtonStates[i] = ButtonState::Held;
						else if (buttonState.IsDown && !buttonState.WasDown)
							controller.ButtonStates[i] = ButtonState::Pressed;
						else
							controller.ButtonStates[i] = ButtonState::Released;
					}
					for (int i = 0; i < (sizeof(gamepadstate.axes)/sizeof(float)); i++) {
						if (justConnected) // Set a moderate deadzone for axes
							controller.AxisDeadZones[i] = defaultDeadzone;
						controller.AxisStates[i] = std::abs(gamepadstate.axes[i]) > controller.AxisDeadZones[i] ? gamepadstate.axes[i] : 0.0f;
					}
				}
				else {
					int buttonCount;
					const unsigned char* buttons = glfwGetJoystickButtons(id, &buttonCount);
					std::map<int, StateInternal>& buttonStates = s_ControllerButtonData[id].ButtonStates;
					for (int i = 0; i < buttonCount; i++) {
						StateInternal& buttonState = buttonStates[i];
						buttonState.WasDown = buttonState.IsDown;
						buttonState.IsDown = (buttons[i] == GLFW_PRESS);

						if (!buttonState.IsDown && !buttonState.WasDown)
							controller.ButtonStates[i] = ButtonState::None;
						else if (buttonState.IsDown && buttonState.WasDown)
							controller.ButtonStates[i] = ButtonState::Held;
						else if (buttonState.IsDown && !buttonState.WasDown)
							controller.ButtonStates[i] = ButtonState::Pressed;
						else
							controller.ButtonStates[i] = ButtonState::Released;
					}

					int axisCount;
					const float* axes = glfwGetJoystickAxes(id, &axisCount);
					for (int i = 0; i < axisCount; i++) {
						if (justConnected) // Set a moderate deadzone for axes
							controller.AxisDeadZones[i] = defaultDeadzone;
						controller.AxisStates[i] = std::abs(axes[i]) > controller.AxisDeadZones[i] ? axes[i] : 0.0f;
					}

					int hatCount;
					const unsigned char* hats = glfwGetJoystickHats(id, &hatCount);
					for (int i = 0; i < hatCount; i++)
						controller.HatStates[i] = static_cast<HatState>(hats[i]);
				}

				if (justConnected) {
					/*
					 *  Instead of relying on glfwSetJoystickCallback for controller connection/disconnection events,
					 *  I have chosen to manage these events along with the rest of the joystick update functionality here.
					 */
					ControllerConnectedEvent event(controller);
					s_EventCallback(event);
				}
			}
			else {
				bool justDisconnected = s_Controllers.find(id) != s_Controllers.end();
				if (justDisconnected) {
					/*
					 *  Instead of relying on glfwSetJoystickCallback for controller connection/disconnection events,
					 *  I have chosen to manage these events along with the rest of the joystick update functionality here.
					 */
					ControllerDisconnectedEvent event(s_Controllers[id]);
					s_Controllers.erase(id);
					s_ControllerButtonData.erase(id);
					s_EventCallback(event);
				}
			}
		}

		// Update key states
		for (std::pair<const KeyCode, KeyStateInternal>& keyDataPair : s_KeyData) {
			KeyStateInternal& keyData = keyDataPair.second;
			if (keyData.IsDown && keyData.WasDown)
				keyData.State = KeyState::Held;
			else if (keyData.IsDown && !keyData.WasDown)
				keyData.State = KeyState::Pressed;
			else if (!keyData.IsDown && keyData.WasDown)
				keyData.State = KeyState::Released;
			else
				keyData.State = KeyState::None;
			keyData.WasDown = keyData.IsDown;
		}

		// Update mouse button states
		for (std::pair<const MouseButton, MouseButtonStateInternal>& mouseButtonDataPair : s_MouseButtonData) {
			MouseButtonStateInternal& mouseButtonData = mouseButtonDataPair.second;
			if (mouseButtonData.IsDown && mouseButtonData.WasDown)
				mouseButtonData.State = KeyState::Held;
			else if (mouseButtonData.IsDown && !mouseButtonData.WasDown)
				mouseButtonData.State = KeyState::Pressed;
			else if (!mouseButtonData.IsDown && mouseButtonData.WasDown)
				mouseButtonData.State = KeyState::Released;
			else
				mouseButtonData.State = KeyState::None;
			mouseButtonData.WasDown = mouseButtonData.IsDown;
		}

	}

	void Input::SetCursorMode(CursorMode mode) {

		switch (mode) {
			case CursorMode::Normal:
				glfwSetInputMode(static_cast<GLFWwindow*>(s_Window), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
			case CursorMode::Hidden:
				glfwSetInputMode(static_cast<GLFWwindow*>(s_Window), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				break;
			case CursorMode::Locked:
				glfwSetInputMode(static_cast<GLFWwindow*>(s_Window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
			default:
				YGE_CORE_WARN("Tried to set cursor mode to invalid value: ({})!", static_cast<int>(mode));
				return;
		}
		s_CursorMode = mode;

	}

}