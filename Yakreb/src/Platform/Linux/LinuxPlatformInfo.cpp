#include "yakrebpch.h"
#include "LinuxPlatformInfo.h"

#include <iostream>
#include <string>
#include <cstring>
#include <sys/utsname.h>

namespace Yakreb {

	void LinuxPlatformInfo::Init() {
        struct utsname native;
        if (uname(&native) > -1) {
            s_OSShortName = native.sysname;
            s_OSVersion = native.release;
        }
        else {
            s_OSShortName = "Unrecognized Linux";
            s_OSVersion = "unknown";
        }

        FILE* pipe = popen("cat /etc/os-release", "r");
        if (!pipe)
            s_OSName = "Unrecognized Linux";
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
                s_OSName = result.substr(pos, end - pos);
                if (s_OSName.size() >= 2 && s_OSName.front() == '"' && s_OSName.back() == '"')
                    s_OSName = s_OSName.substr(1, s_OSName.size() - 2);
            }
            else {
                s_OSName = "Unrecognized Linux";
            }
        }
        s_PlatformString = s_OSName + " Kernel(" + s_OSVersion + ")";
	}

}