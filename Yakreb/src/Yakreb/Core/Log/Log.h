#pragma once

#include "Yakreb/Core/Core.h"

#include "LogHelper.h"

// Ignore warnings raised inside external headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include "CommonMessages.h"

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
			static void PrintMessage(Log::Type type, Log::Level level, std::string_view tag, Args&&... args);

			constexpr const char* GetLevelName(const Level level) {
				switch (level) {
					case Level::Trace: return "Trace";
					case Level::Info:  return "Info";
					case Level::Warn:  return "Warning";
					case Level::Error: return "Error";
					case Level::Fatal: return "Critical Error";
				}
				#ifdef YGE_ENABLE_CORE_LOGS
					PrintMessage(Type::Core, Level::Warn, "", "Unknown log level");
				#endif
				return "";
			}
			inline static bool Initialized() { return s_Initialized; }

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
			static bool s_Initialized;

	};

}

#define YGE_CORE_TRACE_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Trace, tag, __VA_ARGS__)
#define YGE_CORE_INFO_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Info, tag, __VA_ARGS__)
#define YGE_CORE_WARN_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Warn, tag, __VA_ARGS__)
#define YGE_CORE_ERROR_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, tag, __VA_ARGS__)
#define YGE_CORE_FATAL_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Fatal, tag, __VA_ARGS__)

#define YGE_TRACE_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Trace, tag, __VA_ARGS__)
#define YGE_INFO_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Info, tag, __VA_ARGS__)
#define YGE_WARN_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Warn, tag, __VA_ARGS__)
#define YGE_ERROR_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, tag, __VA_ARGS__)
#define YGE_FATAL_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Fatal, tag, __VA_ARGS__)

#define YGE_CORE_TRACE(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Trace, "", __VA_ARGS__)
#define YGE_CORE_INFO(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Info, "", __VA_ARGS__)
#define YGE_CORE_WARN(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Warn, "", __VA_ARGS__)
#define YGE_CORE_ERROR(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, "", __VA_ARGS__)
#define YGE_CORE_FATAL(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Fatal, "", __VA_ARGS__)

#define YGE_TRACE(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Trace, "", __VA_ARGS__)
#define YGE_INFO(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Info, "", __VA_ARGS__)
#define YGE_WARN(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Warn, "", __VA_ARGS__)
#define YGE_ERROR(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, "", __VA_ARGS__)
#define YGE_FATAL(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Fatal, "", __VA_ARGS__)

#ifdef YGE_ENABLE_CORE_LOGS
	#define YGE_CORE_DEBUG_TRACE_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Trace, tag, __VA_ARGS__)
	#define YGE_CORE_DEBUG_INFO_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Info, tag, __VA_ARGS__)
	#define YGE_CORE_DEBUG_WARN_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Warn, tag, __VA_ARGS__)
	#define YGE_CORE_DEBUG_ERROR_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, tag, __VA_ARGS__)
	#define YGE_CORE_DEBUG_FATAL_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Fatal, tag, __VA_ARGS__)

	#define YGE_CORE_DEBUG_TRACE(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Trace, "", __VA_ARGS__)
	#define YGE_CORE_DEBUG_INFO(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Info, "", __VA_ARGS__)
	#define YGE_CORE_DEBUG_WARN(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Warn, "", __VA_ARGS__)
	#define YGE_CORE_DEBUG_ERROR(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Error, "", __VA_ARGS__)
	#define YGE_CORE_DEBUG_FATAL(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Core, ::Yakreb::Log::Level::Fatal, "", __VA_ARGS__)
#else
	#define YGE_CORE_DEBUG_TRACE_TAGGED(tag, ...)
	#define YGE_CORE_DEBUG_INFO_TAGGED(tag, ...)
	#define YGE_CORE_DEBUG_WARN_TAGGED(tag, ...)
	#define YGE_CORE_DEBUG_ERROR_TAGGED(tag, ...)
	#define YGE_CORE_DEBUG_FATAL_TAGGED(tag, ...)

	#define YGE_CORE_DEBUG_TRACE(...)
	#define YGE_CORE_DEBUG_INFO(...) 
	#define YGE_CORE_DEBUG_WARN(...) 
	#define YGE_CORE_DEBUG_ERROR(...)
	#define YGE_CORE_DEBUG_FATAL(...)
#endif

#ifdef YGE_ENABLE_LOGS
	#define YGE_DEBUG_TRACE_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Trace, tag, __VA_ARGS__)
	#define YGE_DEBUG_INFO_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Info, tag, __VA_ARGS__)
	#define YGE_DEBUG_WARN_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Warn, tag, __VA_ARGS__)
	#define YGE_DEBUG_ERROR_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, tag, __VA_ARGS__)
	#define YGE_DEBUG_FATAL_TAGGED(tag, ...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Fatal, tag, __VA_ARGS__)

	#define YGE_DEBUG_TRACE(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Trace, "", __VA_ARGS__)
	#define YGE_DEBUG_INFO(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Info, "", __VA_ARGS__)
	#define YGE_DEBUG_WARN(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Warn, "", __VA_ARGS__)
	#define YGE_DEBUG_ERROR(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Error, "", __VA_ARGS__)
	#define YGE_DEBUG_FATAL(...) ::Yakreb::Log::PrintMessage(::Yakreb::Log::Type::Client, ::Yakreb::Log::Level::Fatal, "", __VA_ARGS__)
#else
	#define YGE_DEBUG_TRACE_TAGGED(tag, ...)
	#define YGE_DEBUG_INFO_TAGGED(tag, ...) 
	#define YGE_DEBUG_WARN_TAGGED(tag, ...) 
	#define YGE_DEBUG_ERROR_TAGGED(tag, ...)
	#define YGE_DEBUG_FATAL_TAGGED(tag, ...)

	#define YGE_DEBUG_TRACE(...)
	#define YGE_DEBUG_INFO(...) 
	#define YGE_DEBUG_WARN(...) 
	#define YGE_DEBUG_ERROR(...)
	#define YGE_DEBUG_FATAL(...)
#endif

namespace Yakreb {

	template<typename... Args>
	inline void Log::PrintMessage(Log::Type type, Log::Level level, std::string_view tag, Args&&... args) {
		std::shared_ptr<spdlog::logger> logger = (type == Type::Core) ? GetCoreLogger() : GetClientLogger();
		const char* logFormat = tag.empty() ? "{0}{1}" : "[{0}] {1}";
		switch (level) {
			case Level::Trace:
				logger->trace(logFormat, tag, fmt::format(std::forward<Args>(args)...));
				break;
			case Level::Info:
				logger->info(logFormat, tag, fmt::format(std::forward<Args>(args)...));
				break;
			case Level::Warn:
				logger->warn(logFormat, tag, fmt::format(std::forward<Args>(args)...));
				break;
			case Level::Error:
				logger->error(logFormat, tag, fmt::format(std::forward<Args>(args)...));
				break;
			case Level::Fatal:
				logger->critical(logFormat, tag, fmt::format(std::forward<Args>(args)...));
				break;
		}
	}

}