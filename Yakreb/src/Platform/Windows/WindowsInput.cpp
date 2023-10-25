#include "yakrebpch.h"
#include "WindowsInput.h"

#include "Yakreb/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Yakreb {

	Input* Input::s_Instance = new WindowsInput();

	WindowsInput::WindowsInput() {

	}

	inline bool WindowsInput::IsKeyPressedImpl(const Key key) {
		GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	inline bool WindowsInput::IsMouseButtonPressedImpl(const Button button) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	inline glm::vec2 WindowsInput::GetMousePositionImpl() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

}