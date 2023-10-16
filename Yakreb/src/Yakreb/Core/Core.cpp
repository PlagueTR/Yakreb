#include "yakrebpch.h"
#include "Yakreb/Core/PlatformInfo.h"
#include "Yakreb/Core/Util/FilesystemHelper.h"
#include "Yakreb/Core/Version.h"

namespace Yakreb {

	void InitializeCore() {

		PlatformInfo::Init();
		FilesystemHelper::Init();
		Log::Init();

		Log::PrintMessage(Log::Type::Core, Log::Level::Trace, "Yakreb Engine - {0}", YGE_VERSION);
		Log::PrintMessage(Log::Type::Core, Log::Level::Trace, "Platform - {0}", PlatformInfo::GetPlatformString());

		YGE_CORE_FATAL("{}", "Example fatal error from core!");
		YGE_CORE_ERROR("{}", "Example error from core!");
		YGE_CORE_WARN("{}", "Example warning from core!");
		YGE_CORE_INFO("{}", "Example info from core!");
		YGE_CORE_TRACE("{}", "Example trace from core!");

		YGE_CORE_ASSERT(10 > 100, "10 is not greater than 100!");
		YGE_CORE_ASSERT(10 < 100, "10 is not less than 100!");

	}

	void ShutdownCore() {

	}

}
