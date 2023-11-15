#pragma once

#include <memory>
#include "Yakreb/Core/Ref.h"

#define BIT(x) (1 << (x))

#define BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)

#include "Yakreb/Core/PlatformDetection.h"
#include "Yakreb/Core/Assert.h"

namespace Yakreb {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;

	void InitializeCore();
	void ShutdownCore();

}
