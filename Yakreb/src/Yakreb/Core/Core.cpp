#include "yakrebpch.h"
#include "Yakreb/Core/PlatformInfo.h"
#include "Yakreb/Core/Util/FilesystemHelper.h"
#include "Yakreb/Core/Version.h"

namespace Yakreb {

	void InitializeCore() {

		PlatformInfo::Init();
		FilesystemHelper::Init();
		Log::Init();

		// We always want to log these
		YGE_CORE_INFO("Yakreb Engine - {0} - {1} Build", YGE_VERSION, YGE_BUILD_CONFIGURATION);
		YGE_CORE_INFO("Platform - {}", PlatformInfo::GetPlatformString());

	}

	void ShutdownCore() {

	}

}
