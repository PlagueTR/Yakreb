#include "yakrebpch.h"
#include "Yakreb/Core/PlatformInfo.h"
#include "Yakreb/Core/Util/FileSystem.h"
#include "Yakreb/Core/Version.h"

#include "Yakreb/Renderer/RendererAPI.h"

namespace Yakreb {

	void InitializeCore() {

		Allocator::Init();

		PlatformInfo::Init();

		FileSystem::Init();

		Log::Init();

		// For now, just set the renderer API to OpenGL
		RendererAPI::SetAPI(RendererAPI::API::OpenGL);

		// We always want to log these
		YGE_CORE_INFO("Yakreb Engine - {0} - {1} Build", YGE_VERSION, YGE_BUILD_CONFIGURATION);
		YGE_CORE_INFO("Platform - {}", PlatformInfo::GetPlatformString());

	}

	void ShutdownCore() {

	}

}
