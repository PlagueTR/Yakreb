#pragma once

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
#elif defined(YGE_RELEASE)
	#define YGE_DEBUGBREAK
	#define YGE_ENABLE_LOGS
	#define YGE_ENABLE_LOG_ONLY_ASSERTS
#elif defined(YGE_DIST)
	#define YGE_DEBUGBREAK
	#define YGE_ENABLE_LOG_ONLY_ASSERTS
#endif

#ifdef YGE_ENABLE_ASSERTS
	#define YGE_CORE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); YGE_DEBUGBREAK; } }
	#define YGE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); YGE_DEBUGBREAK; } }
#elif defined(YGE_ENABLE_LOG_ONLY_ASSERTS)
	#define YGE_CORE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); YGE_DEBUGBREAK; } }
	#define YGE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); YGE_DEBUGBREAK; } }
#else
	#define YGE_CORE_ASSERT(condition, ...)
	#define YGE_ASSERT(condition, ...)
#endif