#include "yakrebpch.h"
#include "FilesystemHelper.h"

#ifdef YGE_PLATFORM_WINDOWS
	#include "Platform/Windows/Util/WindowsFilesystemHelper.h"
#elif defined(YGE_PLATFORM_LINUX)
	#include "Platform/Linux/Util/LinuxFilesystemHelper.h"
#endif

namespace Yakreb {

	std::filesystem::path FilesystemHelper::s_ExecutablePath;
	std::filesystem::path FilesystemHelper::s_ExecutableDirectoryPath;
	std::string FilesystemHelper::s_ExecutableName;

	void FilesystemHelper::Init() {

		#ifdef YGE_PLATFORM_WINDOWS
			WindowsFilesystemHelper::Init();
		#elif defined(YGE_PLATFORM_LINUX)
			LinuxFilesystemHelper::Init();
		#endif

	}

	std::filesystem::file_time_type FilesystemHelper::GetFileCreationTime(const std::filesystem::path& path) {

		#ifdef YGE_PLATFORM_WINDOWS
			return WindowsFilesystemHelper::GetFileCreationTime(path);
		#elif defined(YGE_PLATFORM_LINUX)
			return LinuxFilesystemHelper::GetFileCreationTime(path);
		#endif
		return std::filesystem::file_time_type();

	}

	void FilesystemHelper::SetFileCreationTime(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) {

		#ifdef YGE_PLATFORM_WINDOWS
			WindowsFilesystemHelper::SetFileCreationTime(path, creationTime);
		#elif defined(YGE_PLATFORM_LINUX)
			// Can not modify file creation date on Linux without system specific utilities or libraries such as debugfs
		#endif
	}

}

