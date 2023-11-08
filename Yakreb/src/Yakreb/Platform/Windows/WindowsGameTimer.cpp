#include "yakrebpch.h"
#include "WindowsGameTimer.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	GameTimer* GameTimer::s_Instance = new WindowsGameTimer();

	WindowsGameTimer::WindowsGameTimer() {

	}

	inline void WindowsGameTimer::UpdateGameTimeImpl() {
		GameTime::s_TimeScale = GameTime::s_TimeScaleNext;
		float time = (float)glfwGetTime();
		GameTime::s_DeltaTime = time - GameTime::s_RealTime;
		GameTime::s_ScaledDeltaTime = GameTime::s_DeltaTime * GameTime::s_TimeScale;
		GameTime::s_RealTime = time;
		GameTime::s_ScaledTime += GameTime::s_ScaledDeltaTime;
	}

}