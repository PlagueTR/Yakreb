#include "yakrebpch.h"
#include "GameTimer.h"

#include "Yakreb/Core/GameTime.h"

#include <GLFW/glfw3.h>

namespace Yakreb {

	void GameTimer::UpdateGameTime() {
		float time = (float)glfwGetTime();
		GameTime::s_DeltaTime = time - GameTime::s_RealTime;
		GameTime::s_RealTime = time;
		GameTime::s_ScaledTime += GameTime::GetScaledDeltaTime();
	}

}