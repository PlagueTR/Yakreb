#pragma once
#include <string>

namespace Yakreb {

	class PlatformInfo {
		public:
			static bool IsWindows() {
				#ifdef YGE_PLATFORM_WINDOWS
					return true;
				#endif
				return false;
			}
			static bool IsLinux() {
				#ifdef YGE_PLATFORM_LINUX
					return true;
				#endif
				return false;
			};

			static std::string GetPlatformString() {
				return s_PlatformString;
			}

			static std::string GetOSShortName() {
				return s_OSShortName;
			}

			static std::string GetOSName() {
				return s_OSName;
			}

			static std::string GetOSVersion() {
				return s_OSVersion;
			}

		protected:
			static void Init();

			static std::string s_PlatformString;

			static std::string s_OSShortName;
			static std::string s_OSName;
			static std::string s_OSVersion;

			friend void InitializeCore();

	};

}