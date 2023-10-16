#pragma once

#define BIT(x) (1 << x)

#include "Yakreb/Core/PlatformDetection.h"
#include "Yakreb/Core/Assert.h"

namespace Yakreb {
	void InitializeCore();
	void ShutdownCore();
}
