#pragma once
#include "Yakreb/Core/PlatformInfo.h"

#include <cstdint>
#include <string>
#include <Windows.h>

//Windows version detection heavily based on VersionHelpers.h with finer details and Windows 11 detection support
// Adapted from https://github.com/DarthTon/Blackbone/blob/master/src/3rd_party/VersionApi.h

#define _WIN32_WINNT_NT4            0x0400
#define _WIN32_WINNT_WIN2K          0x0500
#define _WIN32_WINNT_WINXP          0x0501
#define _WIN32_WINNT_WS03           0x0502
#define _WIN32_WINNT_WIN6           0x0600
#define _WIN32_WINNT_VISTA          0x0600
#define _WIN32_WINNT_WS08           0x0600
#define _WIN32_WINNT_LONGHORN       0x0600
#define _WIN32_WINNT_WIN7           0x0601
#define _WIN32_WINNT_WIN8           0x0602
#define _WIN32_WINNT_WINBLUE        0x0603
#define _WIN32_WINNT_WIN10          0x0A00 

namespace Yakreb {

    class WindowsPlatformInfo : public PlatformInfo {
        public:
            WindowsPlatformInfo();

        private:
            enum WindowsBuildThreshold
            {
                Build_RS0 = 10586,
                Build_RS1 = 14393,
                Build_RS2 = 15063,
                Build_RS3 = 16299,
                Build_RS4 = 17134,
                Build_RS5 = 17763,
                Build_19H1 = 18362,
                Build_19H2 = 18363,
                Build_20H1 = 19041,
                Build_21H2 = 22000,
                Build_22H2 = 22621,
                Build_RS_MAX = 99999
            };

            enum class WindowsVersionShort
            {
                WinUnsupported, // Unsupported OS 
                WinXP,          // Windows XP
                Win7,           // Windows 7
                Win8,           // Windows 8
                Win8Point1,     // Windows 8.1
                Win10,          // Windows 10
                Win10_RS1,      // Windows 10 Anniversary update
                Win10_RS2,      // Windows 10 Creators update
                Win10_RS3,      // Windows 10 Fall Creators update
                Win10_RS4,      // Windows 10 Spring Creators update
                Win10_RS5,      // Windows 10 October 2018 update
                Win10_19H1,     // Windows 10 May 2019 update
                Win10_19H2,     // Windows 10 November 2019 update
                Win10_20H1,     // Windows 10 April 2020 update
                Win11_21H2,     // Windows 11
                Win11_22H2      // Windows 11 September 2022 update
            };

    };

}