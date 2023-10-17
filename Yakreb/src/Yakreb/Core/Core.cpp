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
		YGE_CORE_INFO("Yakreb Engine - {}", YGE_VERSION);
		YGE_CORE_INFO("Platform - {}", PlatformInfo::GetPlatformString());

	}

	void ShutdownCore() {

	}

}
