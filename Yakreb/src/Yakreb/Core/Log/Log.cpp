#include "yakrebpch.h"
#include "Log.h"

#include "Yakreb/Core/Util/FileSystem.h"

// Ignore warnings raised inside external headers
#pragma warning(push, 0)
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma warning(pop)

namespace Yakreb {

	bool Log::s_Initialized = false;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger = nullptr;

	void Log::Init() {

		//How many log files to keep
		unsigned int maxLogCount = 9;

		std::string latestLog = "latest.log";
		std::filesystem::path logsDirectory = FileSystem::GetExecutableDirectoryPath() / "logs";
		std::filesystem::path latestLogPath = logsDirectory / latestLog;

		if (!std::filesystem::exists(logsDirectory))
			std::filesystem::create_directories(logsDirectory);

		// Get a list of logs and rename latest.log to it's creation date if exists
		std::vector<std::filesystem::path> logFiles;
		for (const auto& entry : std::filesystem::directory_iterator(logsDirectory)) {
			if (entry.is_regular_file() && entry.path().extension() == ".log") {
				if (entry.path().filename() == latestLog) {
					std::filesystem::file_time_type creationTime = FileSystem::GetFileCreationTime(entry.path());
					std::chrono::system_clock::time_point timePoint(creationTime.time_since_epoch());
					time_t time = std::chrono::system_clock::to_time_t(timePoint);
					std::tm *timeInfo = std::localtime(&time);
					char newFileName[256];
					std::strftime(newFileName, sizeof(newFileName), "%Y-%m-%d_%H-%M-%S", timeInfo);
					std::filesystem::rename(entry.path(), logsDirectory / (std::string(newFileName) + ".log"));
				}
				else {
					logFiles.push_back(entry.path());
				}
			}
		}

		// Delete logs if we have too many log files
		if (logFiles.size() > maxLogCount) {
			std::sort(logFiles.begin(), logFiles.end());

			int filesToDelete = (int)logFiles.size() - maxLogCount;
			for (int i = 0; i < filesToDelete; i++) {
				std::filesystem::remove(logFiles[i]);
			}
		}

		// Create logging sinks & register loggers
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(latestLogPath.string(), true));

		logSinks[0]->set_pattern("%^[%T] [%n/%l]: %v%$");
		logSinks[1]->set_pattern("[%T] [%n/%l]: %v");

		s_CoreLogger = std::make_shared<spdlog::logger>("YGE", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);

		// This is mostly for Windows systems
		//   Windows has "filesystem tunneling" feature, which is basically caching files' creation times
		//   because many applications would delete and recreate configuration files when an option was changed
		//   rather than updating/altering the file
		// If we do not use this, the latest.log file keep it's original creation date and will override the older log
		FileSystem::SetFileCreationTime(latestLogPath, std::filesystem::file_time_type(std::chrono::system_clock::now().time_since_epoch()));

		s_Initialized = true;

	}

	void Log::Shutdown() {
		s_ClientLogger.reset();
		s_CoreLogger.reset();
		spdlog::drop_all();
	}

}