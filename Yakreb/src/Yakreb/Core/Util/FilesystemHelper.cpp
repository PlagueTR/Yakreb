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

}

