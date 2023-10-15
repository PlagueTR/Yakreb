#pragma once
#include "Yakreb/Core/PlatformInfo.h"

namespace Yakreb {

    class LinuxPlatformInfo : public PlatformInfo {

        private:
            static void Init();

            friend void PlatformInfo::Init();

    };

}
