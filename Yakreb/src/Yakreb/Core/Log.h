#pragma once

#include "Yakreb/Core/Core.h"

// Ignore warnings raised inside external headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Yakreb {

	class Log {
		public:
			enum class Type : uint8_t {
				Core = 0,
				Client = 1
			};

			enum Level : uint8_t {
				Trace = BIT(0),
				Info = BIT(1),
				Warn = BIT(2),
				Error = BIT(3),
				Fatal = BIT(4)
			};

			static void Init();
			static void Shutdown();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

			template<typename... Args>
			static void PrintMessage(Log::Type type, Log::Level level, const std::string &logFormat, Args&&... args);

			constexpr const char* GetLevelName(const Level level) {
				switch (level) {
					case Level::Info:  return "INFO";
					case Level::Warn:  return "WARN";
					case Level::Error: return "ERROR";
					case Level::Fatal: return "FATAL";
					default:           return "TRACE";
				}
			}

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

#define YGE_CORE_TRACE(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Trace, logFormat, __VA_ARGS__)
#define YGE_CORE_INFO(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Info, logFormat, __VA_ARGS__)
#define YGE_CORE_WARN(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Warn, logFormat, __VA_ARGS__)
#define YGE_CORE_ERROR(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, logFormat, __VA_ARGS__)
#define YGE_CORE_FATAL(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Fatal, logFormat, __VA_ARGS__)

#define YGE_TRACE(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Trace, logFormat, __VA_ARGS__)
#define YGE_INFO(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Info, logFormat, __VA_ARGS__)
#define YGE_WARN(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Warn, logFormat, __VA_ARGS__)
#define YGE_ERROR(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, logFormat, __VA_ARGS__)
#define YGE_FATAL(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Fatal, logFormat, __VA_ARGS__)

#ifdef YGE_ENABLE_CORE_LOGS
	#define YGE_CORE_DEBUG_TRACE(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Trace, logFormat, __VA_ARGS__)
	#define YGE_CORE_DEBUG_INFO(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Info, logFormat, __VA_ARGS__)
	#define YGE_CORE_DEBUG_WARN(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Warn, logFormat, __VA_ARGS__)
	#define YGE_CORE_DEBUG_ERROR(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, logFormat, __VA_ARGS__)
	#define YGE_CORE_DEBUG_FATAL(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Fatal, logFormat, __VA_ARGS__)
#else
	#define YGE_CORE_DEBUG_TRACE(logFormat, ...)
	#define YGE_CORE_DEBUG_INFO(logFormat, ...) 
	#define YGE_CORE_DEBUG_WARN(logFormat, ...) 
	#define YGE_CORE_DEBUG_ERROR(logFormat, ...)
	#define YGE_CORE_DEBUG_FATAL(logFormat, ...)
#endif

#ifdef YGE_ENABLE_LOGS
	#define YGE_DEBUG_TRACE(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Trace, logFormat, __VA_ARGS__)
	#define YGE_DEBUG_INFO(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Info, logFormat, __VA_ARGS__)
	#define YGE_DEBUG_WARN(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Warn, logFormat, __VA_ARGS__)
	#define YGE_DEBUG_ERROR(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, logFormat, __VA_ARGS__)
	#define YGE_DEBUG_FATAL(logFormat, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Fatal, logFormat, __VA_ARGS__)
#else
	#define YGE_DEBUG_TRACE(logFormat, ...)
	#define YGE_DEBUG_INFO(logFormat, ...) 
	#define YGE_DEBUG_WARN(logFormat, ...) 
	#define YGE_DEBUG_ERROR(logFormat, ...)
	#define YGE_DEBUG_FATAL(logFormat, ...)
#endif

namespace Yakreb {

	template<typename ...Args>
	void Log::PrintMessage(Log::Type type, Log::Level level, const std::string &logFormat, Args&&... args) {
		std::shared_ptr<spdlog::logger> logger = (type == Type::Core) ? GetCoreLogger() : GetClientLogger();
		switch (level) {
			case Level::Trace:
				logger->trace(logFormat, std::forward<Args>(args)...);
				break;
			case Level::Info:
				logger->info(logFormat, std::forward<Args>(args)...);
				break;
			case Level::Warn:
				logger->warn(logFormat, std::forward<Args>(args)...);
				break;
			case Level::Error:
				logger->error(logFormat, std::forward<Args>(args)...);
				break;
			case Level::Fatal:
				logger->critical(logFormat, std::forward<Args>(args)...);
				break;
		}
	}

}