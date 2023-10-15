#ifndef YAKREB_PCH_H
#define YAKREB_PCH_H

#include "Yakreb/Core/PlatformDetection.h"

#ifdef YGE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>


#ifdef YGE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include "Yakreb/Core/Core.h"
#include "Yakreb/Core/PlatformInfo.h"
#include "Yakreb/Core/Util/FilesystemHelper.h"
#include "Yakreb/Core/Log.h"

#endif