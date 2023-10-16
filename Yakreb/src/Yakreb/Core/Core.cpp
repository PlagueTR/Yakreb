#include "yakrebpch.h"
#include "Yakreb/Core/PlatformInfo.h"
#include "Yakreb/Core/Util/FilesystemHelper.h"
#include "Yakreb/Core/Version.h"

namespace Yakreb {

	void InitializeCore() {

		PlatformInfo::Init();
		FilesystemHelper::Init();
		Log::Init();

		// We always want to log these - do not use YGE_CORE_TRACE macro here
		Log::PrintMessage(Log::Type::Core, Log::Level::Trace, "Yakreb Engine - {0}", YGE_VERSION);
		Log::PrintMessage(Log::Type::Core, Log::Level::Trace, "Platform - {0}", PlatformInfo::GetPlatformString());

	}

	void ShutdownCore() {

	}

}
