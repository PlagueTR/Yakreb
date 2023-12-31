#include "yakrebpch.h"
#include "Yakreb/Core/PlatformInfo.h"

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

namespace Yakreb {

    std::string PlatformInfo::s_PlatformString;
    std::string PlatformInfo::s_OSShortName;
    std::string PlatformInfo::s_OSName;
    std::string PlatformInfo::s_OSVersion;

	void PlatformInfo::Init() {
        PlatformInfo::s_OSShortName = "Windows";

        RTL_OSVERSIONINFOEXW native{ 0 };
        native.dwOSVersionInfoSize = sizeof(native);

        using fnRtlGetVersion = NTSTATUS(NTAPI*)(PRTL_OSVERSIONINFOEXW lpVersionInformation);

        fnRtlGetVersion RtlGetVersion;
        if (auto ntdllModule = GetModuleHandleW(L"ntdll.dll")) {
            RtlGetVersion = (fnRtlGetVersion)GetProcAddress(ntdllModule, "RtlGetVersion");
            if (RtlGetVersion)
                RtlGetVersion(&native);
        }

        if (native.dwMajorVersion != 0)
        {
            PlatformInfo::s_OSVersion = std::to_string(native.dwBuildNumber);

            unsigned long fullver = (native.dwMajorVersion << 8) | native.dwMinorVersion;
            switch (fullver)
            {
            case _WIN32_WINNT_WIN10:
                if (native.dwBuildNumber >= WindowsBuildThreshold::Build_22H2)
                    PlatformInfo::s_OSName = "Windows 11 22H2";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_21H2)
                    PlatformInfo::s_OSName = "Windows 11 21H2";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_20H1)
                    PlatformInfo::s_OSName = "Windows 10 20H1";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_19H2)
                    PlatformInfo::s_OSName = "Windows 10 19H2";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_19H1)
                    PlatformInfo::s_OSName = "Windows 10 19H1";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_RS5)
                    PlatformInfo::s_OSName = "Windows 10 RS5";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_RS4)
                    PlatformInfo::s_OSName = "Windows 10 RS4";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_RS3)
                    PlatformInfo::s_OSName = "Windows 10 RS3";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_RS2)
                    PlatformInfo::s_OSName = "Windows 10 RS2";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_RS1)
                    PlatformInfo::s_OSName = "Windows 10 RS1";
                else if (native.dwBuildNumber >= WindowsBuildThreshold::Build_RS0)
                    PlatformInfo::s_OSName = "Windows 10 TH2";
                else
                    PlatformInfo::s_OSName = "Windows 10";
                break;
            case _WIN32_WINNT_WINBLUE:
                PlatformInfo::s_OSName = "Windows 8.1";
                break;

            case _WIN32_WINNT_WIN8:
                PlatformInfo::s_OSName = "Windows 8";
                break;

            case _WIN32_WINNT_WIN7:
                if (native.wServicePackMajor > 1)
                    PlatformInfo::s_OSName = "Windows 7 SP1";
                else
                    PlatformInfo::s_OSName = "Windows 7";
                break;

            case _WIN32_WINNT_VISTA:
                if (native.wServicePackMajor > 2)
                    PlatformInfo::s_OSName = "Windows Vista SP2";
                else if (native.wServicePackMajor > 1)
                    PlatformInfo::s_OSName = "Windows Vista SP1";
                else
                    PlatformInfo::s_OSName = "Windows Vista";
                break;

            case _WIN32_WINNT_WINXP:
                if (native.wServicePackMajor > 3)
                    PlatformInfo::s_OSName = "Windows XP SP3";
                else if (native.wServicePackMajor > 2)
                    PlatformInfo::s_OSName = "Windows XP SP2";
                else if (native.wServicePackMajor > 1)
                    PlatformInfo::s_OSName = "Windows XP SP1";
                else
                    PlatformInfo::s_OSName = "Windows XP";
                break;

            default:
                PlatformInfo::s_OSName = "Unrecognized Windows";
            }
        }
        else {
            PlatformInfo::s_OSName = "Unrecognized Windows";
            PlatformInfo::s_OSVersion = "unknown";
        }

        PlatformInfo::s_PlatformString = PlatformInfo::s_OSName + " Build(" + PlatformInfo::s_OSVersion + ")";
	}

}