#pragma once

#include "Yakreb/Core/PlatformDetection.h"

#ifdef YGE_DEBUG
	#if defined(YGE_PLATFORM_WINDOWS)
		#define YGE_DEBUGBREAK __debugbreak()
	#elif defined(YGE_PLATFORM_LINUX)
		#include <signal.h>
		#define YGE_DEBUGBREAK raise(SIGTRAP)
	#else
		// Platforms that don't support debug break yet
		#define YGE_DEBUGBREAK
	#endif
	#define YGE_ENABLE_CORE_LOGS
	#define YGE_ENABLE_LOGS
	#define YGE_ENABLE_ASSERTS
	#define YGE_TRACK_MEMORY
#elif defined(YGE_RELEASE)
	#define YGE_DEBUGBREAK
	#define YGE_ENABLE_LOGS
	#define YGE_ENABLE_LOG_ONLY_ASSERTS
	#define YGE_TRACK_MEMORY
#elif defined(YGE_DIST)
	#define YGE_DEBUGBREAK
	#define YGE_ENABLE_LOG_ONLY_ASSERTS
#endif