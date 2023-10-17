#pragma once

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)

#include "Yakreb/Core/PlatformDetection.h"
#include "Yakreb/Core/Assert.h"

namespace Yakreb {
	void InitializeCore();
	void ShutdownCore();
}
