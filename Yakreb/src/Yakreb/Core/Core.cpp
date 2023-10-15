#include "yakrebpch.h"
#include "Yakreb/Core/Version.h"

namespace Yakreb {

	void InitializeCore() {

		PlatformInfo::Init();
		FilesystemHelper::Init();
		Log::Init();

		Log::GetCoreLogger().get()->trace("Yakreb Engine " + std::string(YGE_VERSION));
		Log::GetCoreLogger().get()->trace("Platform: " + PlatformInfo::GetPlatformString());

	}

	void ShutdownCore() {

	}

}
