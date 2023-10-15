#include "yakrebpch.h"
#include "WindowsPlatformInfo.h"

namespace Yakreb {

    using fnRtlGetVersion = NTSTATUS(NTAPI*)(PRTL_OSVERSIONINFOEXW lpVersionInformation);

	void WindowsPlatformInfo::Init() {
        s_OSShortName = "Windows";

        RTL_OSVERSIONINFOEXW native;
        native.dwOSVersionInfoSize = sizeof(native);

        fnRtlGetVersion RtlGetVersion;
        if (auto ntdllModule = GetModuleHandleW(L"ntdll.dll")) {
            RtlGetVersion = (fnRtlGetVersion)GetProcAddress(ntdllModule, "RtlGetVersion");
            if (RtlGetVersion)
                RtlGetVersion(&native);
        }

        if (native.dwMajorVersion != 0)
        {
            s_OSVersion = std::to_string(native.dwBuildNumber);

            unsigned long fullver = (native.dwMajorVersion << 8) | native.dwMinorVersion;
            switch (fullver)
            {
            case _WIN32_WINNT_WIN10:
                if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_22H2)
                    s_OSName = "Windows 11 22H2";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_21H2)
                    s_OSName = "Windows 11 21H2";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_20H1)
                    s_OSName = "Windows 10 20H1";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_19H2)
                    s_OSName = "Windows 10 19H2";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_19H1)
                    s_OSName = "Windows 10 19H1";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_RS5)
                    s_OSName = "Windows 10 RS5";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_RS4)
                    s_OSName = "Windows 10 RS4";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_RS3)
                    s_OSName = "Windows 10 RS3";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_RS2)
                    s_OSName = "Windows 10 RS2";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_RS1)
                    s_OSName = "Windows 10 RS1";
                else if (native.dwBuildNumber >= (int)WindowsBuildThreshold::Build_RS0)
                    s_OSName = "Windows 10 TH2";
                else
                    s_OSName = "Windows 10";
                break;
            case _WIN32_WINNT_WINBLUE:
                s_OSName = "Windows 8.1";
                break;

            case _WIN32_WINNT_WIN8:
                s_OSName = "Windows 8";
                break;

            case _WIN32_WINNT_WIN7:
                if (native.wServicePackMajor > 1)
                    s_OSName = "Windows 7 SP1";
                else
                    s_OSName = "Windows 7";
                break;

            case _WIN32_WINNT_VISTA:
                if (native.wServicePackMajor > 2)
                    s_OSName = "Windows Vista SP2";
                else if (native.wServicePackMajor > 1)
                    s_OSName = "Windows Vista SP1";
                else
                    s_OSName = "Windows Vista";
                break;

            case _WIN32_WINNT_WINXP:
                if (native.wServicePackMajor > 3)
                    s_OSName = "Windows XP SP3";
                else if (native.wServicePackMajor > 2)
                    s_OSName = "Windows XP SP2";
                else if (native.wServicePackMajor > 1)
                    s_OSName = "Windows XP SP1";
                else
                    s_OSName = "Windows XP";
                break;

            default:
                s_OSName = "Unrecognized Windows";
            }
        }
        else {
            s_OSName = "Unrecognized Windows";
            s_OSVersion = "unknown";
        }

        s_PlatformString = s_OSName + " Build(" + s_OSVersion + ")";
	}

}