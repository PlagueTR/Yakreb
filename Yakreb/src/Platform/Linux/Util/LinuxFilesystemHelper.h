#pragma once
#include "Yakreb/Core/Util/FilesystemHelper.h"

namespace Yakreb {

	class LinuxFilesystemHelper : public FilesystemHelper {
		private:
			static void Init();

			friend void ::Yakreb::FilesystemHelper::Init();

	};

}