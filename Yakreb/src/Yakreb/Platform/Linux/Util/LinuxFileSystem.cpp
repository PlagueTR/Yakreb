#include "yakrebpch.h"
#include "Yakreb/Core/Util/FileSystem.h"

#include <sys/stat.h>

namespace Yakreb {

	std::filesystem::path FileSystem::s_ExecutablePath;
	std::filesystem::path FileSystem::s_ExecutableDirectoryPath;
	std::string FileSystem::s_ExecutableName;

	void FileSystem::Init() {
		char buffer[PATH_MAX];
		ssize_t len = readlink("/proc/self/exe", buffer, PATH_MAX);
		if (len != -1) {
			buffer[len] = '\0';
			FileSystem::s_ExecutablePath = std::filesystem::canonical(buffer);
			FileSystem::s_ExecutableDirectoryPath = FileSystem::s_ExecutablePath.parent_path();
			FileSystem::s_ExecutableName = FileSystem::s_ExecutablePath.filename().string();
		}
	}

	std::filesystem::file_time_type FileSystem::GetFileCreationTime(const std::filesystem::path& path) {
		struct stat fileStat;
		std::filesystem::file_time_type returnValue;
		if (stat(path.string().c_str(), &fileStat) == 0) {
			time_t creationTime = fileStat.st_ctime;

			std::chrono::seconds secs(creationTime);

			std::chrono::time_point<std::filesystem::__file_clock, std::filesystem::__file_clock::duration> timePoint(std::chrono::duration_cast<std::chrono::system_clock::duration>(secs));

			returnValue = std::filesystem::file_time_type(timePoint);
		}
		return returnValue;
	}

	// Can not modify file creation date on Linux without system specific utilities or libraries such as debugfs
	void FileSystem::SetFileCreationTime(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) {

	}

}