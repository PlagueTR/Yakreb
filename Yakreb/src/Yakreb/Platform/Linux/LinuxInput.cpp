#include "yakrebpch.h"

#include "Yakreb/Core/Input/Input.h"
#include "Yakreb/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	char* detail::Input::unicodeBuffer = new char[5];

	void* Input::s_NativeWindow = nullptr;

	void Input::Init() {
		s_NativeWindow = Application::Get().GetWindow().GetNativeWindow();
	}

	bool Input::IsKeyPressed(const Key key) {
		GLFWwindow* window = static_cast<GLFWwindow*>(s_NativeWindow);
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(const Button button) {
		GLFWwindow* window = static_cast<GLFWwindow*>(s_NativeWindow);
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition() {
		GLFWwindow* window = static_cast<GLFWwindow*>(s_NativeWindow);
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

}