#pragma once

#include "Yakreb/Core/ConfigMacros.h"

#ifdef YGE_ENABLE_ASSERTS
	#define YGE_CORE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); YGE_DEBUGBREAK; } }
	#define YGE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); YGE_DEBUGBREAK; } }
#elif defined(YGE_ENABLE_LOG_ONLY_ASSERTS)
	#define YGE_CORE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); } }
	#define YGE_ASSERT(condition, ...) { if(!(condition)) { ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, "Assertion Failed: {0}", __VA_ARGS__); } }
#else
	#define YGE_CORE_ASSERT(condition, ...)
	#define YGE_ASSERT(condition, ...)
#endif