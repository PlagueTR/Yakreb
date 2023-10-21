#include "yakrebpch.h"
#include "LinuxFilesystemHelper.h"

#include <sys/stat.h>

namespace Yakreb {

	std::filesystem::path FilesystemHelper::s_ExecutablePath;
	std::filesystem::path FilesystemHelper::s_ExecutableDirectoryPath;
	std::string FilesystemHelper::s_ExecutableName;

	FilesystemHelper* FilesystemHelper::s_Instance = new LinuxFilesystemHelper();

	LinuxFilesystemHelper::LinuxFilesystemHelper() {
		char buffer[PATH_MAX];
		ssize_t len = readlink("/proc/self/exe", buffer, PATH_MAX);
		if (len != -1) {
			buffer[len] = '\0';
			FilesystemHelper::s_ExecutablePath = std::filesystem::canonical(buffer);
			FilesystemHelper::s_ExecutableDirectoryPath = FilesystemHelper::s_ExecutablePath.parent_path();
			FilesystemHelper::s_ExecutableName = FilesystemHelper::s_ExecutablePath.filename().string();
		}
	}

	inline std::filesystem::file_time_type LinuxFilesystemHelper::GetFileCreationTimeImpl(const std::filesystem::path& path) {
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
	inline void LinuxFilesystemHelper::SetFileCreationTimeImpl(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) {

	}

}