
// Platform detection using predefined macros

#ifdef _WIN32
	// Windows x64/x86
	#ifdef _WIN64
		// Windows x64
		#define YGE_PLATFORM_WINDOWS
	#else
		// Windows x86
		#error "Yakreb only supports 64 bit platforms!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	// Apple platforms
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		// IOS simulator
		#error "Yakreb does not support IOS simulator!"
	#elif TARGET_OS_IPHONE == 1
		// IOS
		#define YGE_PLATFORM_IOS
		#error "Yakreb does not support IOS!"
	#elif TARGET_OS_MAC == 1
		// MacOS
		#define YGE_PLATFORM_MACOS
		#error "Yakreb does not support MacOS!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	// Android
	#define YGE_PLATFORM_ANDROID
	#error "Yakreb does not support Android!"
#elif defined(__linux__)
	// Linux
	#define YGE_PLATFORM_LINUX
#else
	#error "Unknown platform!"
#endif
