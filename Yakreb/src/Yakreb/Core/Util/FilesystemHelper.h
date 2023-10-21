#pragma once
#include <filesystem>

namespace Yakreb {

	class FilesystemHelper {
		public:
			inline static std::filesystem::path GetExecutablePath() {
				return s_ExecutablePath;
			}

			inline static std::filesystem::path GetExecutableDirectoryPath() {
				return s_ExecutableDirectoryPath;
			}

			inline static std::string GetExecutableName() {
				return s_ExecutableName;
			}

			inline static std::filesystem::file_time_type GetFileCreationTime(const std::filesystem::path& path) {
				return s_Instance->GetFileCreationTimeImpl(path);
			}

			// This is mostly for Windows systems
			//   Windows has "filesystem tunneling" feature, which is basically caching files' creation times
			//   because many applications would delete and recreate configuration files when an option was changed
			//   rather than updating/altering the file
			inline static void SetFileCreationTime(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) {
				s_Instance->SetFileCreationTimeImpl(path, creationTime);
			}

		protected:

			virtual inline std::filesystem::file_time_type GetFileCreationTimeImpl(const std::filesystem::path& path) = 0;
			virtual inline void SetFileCreationTimeImpl(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) = 0;

			static std::filesystem::path s_ExecutablePath;
			static std::filesystem::path s_ExecutableDirectoryPath;
			static std::string s_ExecutableName;

			static FilesystemHelper* s_Instance;

	};

}