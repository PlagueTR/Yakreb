#ifndef YAKREB_PCH_H
#define YAKREB_PCH_H

#include "Yakreb/Core/Core.h"

#ifdef YGE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <memory>
#include <filesystem>

#include <string_view>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#ifdef YGE_PLATFORM_WINDOWS
	#include <Windows.h>
#elif defined(YGE_PLATFORM_LINUX)
	#include <unistd.h>
#endif

#include "Yakreb/Core/Assert.h"
#include "Yakreb/Core/Core.h"
#include "Yakreb/Core/Events/Event.h"
#include "Yakreb/Core/Log/Log.h"
#include "Yakreb/Core/Memory.h"

#endif