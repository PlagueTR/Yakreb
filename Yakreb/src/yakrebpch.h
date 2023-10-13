#pragma once

#include "Yakreb/Core/PlatformDetection.h"

#ifdef YGE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Yakreb/Core/Core.h"
#include "Yakreb/Core/PlatformInfo.h"

#ifdef YGE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif