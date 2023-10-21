#include "yakrebpch.h"
#include "OpenGLGameTimer.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	GameTimer* GameTimer::s_Instance = new OpenGLGameTimer();

	OpenGLGameTimer::OpenGLGameTimer() {

	}

	inline void OpenGLGameTimer::UpdateGameTimeImpl() {
		float time = (float)glfwGetTime();
		GameTime::s_DeltaTime = time - GameTime::s_RealTime;
		GameTime::s_RealTime = time;
		GameTime::s_ScaledTime += GameTime::GetScaledDeltaTime();
	}

}