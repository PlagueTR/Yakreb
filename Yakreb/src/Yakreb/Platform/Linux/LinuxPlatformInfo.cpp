#include "yakrebpch.h"

#include "Yakreb/Core/PlatformInfo.h"

#include <cstring>
#include <sys/utsname.h>

namespace Yakreb {

    std::string PlatformInfo::s_PlatformString;
    std::string PlatformInfo::s_OSShortName;
    std::string PlatformInfo::s_OSName;
    std::string PlatformInfo::s_OSVersion;

	void PlatformInfo::Init() {
        struct utsname native;
        if (uname(&native) > -1) {
            PlatformInfo::s_OSShortName = native.sysname;
            PlatformInfo::s_OSVersion = native.release;
        }
        else {
            PlatformInfo::s_OSShortName = "Unrecognized Linux";
            PlatformInfo::s_OSVersion = "unknown";
        }

        // most modern Linux distros have /etc/os-release
        FILE* pipe = popen("cat /etc/os-release", "r");
        if (!pipe)
            PlatformInfo::s_OSName = "Unrecognized Linux";
        else {
            char buffer[2048];
            std::string result = "";
            while (!feof(pipe)) {
                if (fgets(buffer, 2048, pipe) != nullptr) {
                    result += buffer;
                }
            }
            pclose(pipe);
            size_t pos = result.find("PRETTY_NAME=");
            if (pos != std::string::npos) {
                pos += strlen("PRETTY_NAME=");
                size_t end = result.find("\n", pos);
                PlatformInfo::s_OSName = result.substr(pos, end - pos);
                if (PlatformInfo::s_OSName.size() >= 2 && PlatformInfo::s_OSName.front() == '"' && PlatformInfo::s_OSName.back() == '"')
                    PlatformInfo::s_OSName = PlatformInfo::s_OSName.substr(1, PlatformInfo::s_OSName.size() - 2);
            }
            else {
                PlatformInfo::s_OSName = "Unrecognized Linux";
            }
        }
        PlatformInfo::s_PlatformString = PlatformInfo::s_OSName + " Kernel(" + PlatformInfo::s_OSVersion + ")";
	}

}