#include "yakrebpch.h"
#include "Yakreb/Core/Version.h"

namespace Yakreb {

	void InitializeCore() {

		PlatformInfo::Init();

		std::cout << "Yakreb Engine " << YGE_VERSION << "\n";
		std::cout << "Platform: " << PlatformInfo::GetPlatformString() << "\n";

	}

	void ShutdownCore() {

	}

}
