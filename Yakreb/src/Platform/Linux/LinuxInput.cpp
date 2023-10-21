#include "yakrebpch.h"
#include "LinuxInput.h"

#include "Yakreb/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Yakreb {

	Input* Input::s_Instance = new LinuxInput();

	LinuxInput::LinuxInput() {

	}

	bool LinuxInput::IsKeyPressedImpl(const Key key) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool LinuxInput::IsMouseButtonPressedImpl(const Button button) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

}