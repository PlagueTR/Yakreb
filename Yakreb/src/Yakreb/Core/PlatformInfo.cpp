#include "yakrebpch.h"

#ifdef YGE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsPlatformInfo.h"
#elif defined(YGE_PLATFORM_LINUX)
	#include "Platform/Linux/LinuxPlatformInfo.h"
#endif

namespace Yakreb {

	std::string PlatformInfo::s_PlatformString = "";
	std::string PlatformInfo::s_OSShortName = "";
	std::string PlatformInfo::s_OSName = "";
	std::string PlatformInfo::s_OSVersion = "";

	void PlatformInfo::Init() {

		#ifdef YGE_PLATFORM_WINDOWS
			WindowsPlatformInfo::Init();
		#elif defined(YGE_PLATFORM_LINUX)
			LinuxPlatformInfo::Init();
		#endif

	}

}
