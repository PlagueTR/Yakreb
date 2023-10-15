#pragma once
#include <filesystem>

namespace Yakreb {

	class FilesystemHelper {
		public:
			static std::filesystem::path GetExecutablePath() {
				return s_ExecutablePath;
			}

			static std::filesystem::path GetExecutableDirectoryPath() {
				return s_ExecutableDirectoryPath;
			}

			static std::string GetExecutableName() {
				return s_ExecutableName;
			}

			static std::filesystem::file_time_type GetFileCreationTime(const std::filesystem::path& path);

			static void SetFileCreationTime(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime);

		protected:
			static void Init();

			static std::filesystem::path s_ExecutablePath;
			static std::filesystem::path s_ExecutableDirectoryPath;
			static std::string s_ExecutableName;

			friend void InitializeCore();

	};

}