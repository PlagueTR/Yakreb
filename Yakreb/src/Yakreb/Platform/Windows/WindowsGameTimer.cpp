#include "yakrebpch.h"

#include "Yakreb/Core/GameTimer.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	float GameTime::s_RealTime = 0.0f;
	float GameTime::s_ScaledTime = 0.0f;

	float GameTime::s_TimeScale = 1.0f;
	float GameTime::s_TimeScaleNext = 1.0f;

	float GameTime::s_DeltaTime = 0.0f;
	float GameTime::s_ScaledDeltaTime = 0.0f;

	void GameTimer::UpdateGameTime() {
		GameTime::s_TimeScale = GameTime::s_TimeScaleNext;
		float time = static_cast<float>(glfwGetTime());
		GameTime::s_DeltaTime = time - GameTime::s_RealTime;
		GameTime::s_ScaledDeltaTime = GameTime::s_DeltaTime * GameTime::s_TimeScale;
		GameTime::s_RealTime = time;
		GameTime::s_ScaledTime += GameTime::s_ScaledDeltaTime;
	}

}