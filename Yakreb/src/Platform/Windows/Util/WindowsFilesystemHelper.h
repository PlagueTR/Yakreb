#pragma once
#include "Yakreb/Core/Util/FilesystemHelper.h"

namespace Yakreb {

	class WindowsFilesystemHelper : public FilesystemHelper {
		private:
			static void Init();

			friend void ::Yakreb::FilesystemHelper::Init();

	};

}