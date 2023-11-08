#include "yakrebpch.h"
#include "LinuxGameTimer.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	GameTimer* GameTimer::s_Instance = new LinuxGameTimer();

	LinuxGameTimer::LinuxGameTimer() {

	}

	inline void LinuxGameTimer::UpdateGameTimeImpl() {
		GameTime::s_TimeScale = GameTime::s_TimeScaleNext;
		float time = (float)glfwGetTime();
		GameTime::s_DeltaTime = time - GameTime::s_RealTime;
		GameTime::s_ScaledDeltaTime = GameTime::s_DeltaTime * GameTime::s_TimeScale;
		GameTime::s_RealTime = time;
		GameTime::s_ScaledTime += GameTime::s_ScaledDeltaTime;
	}

}