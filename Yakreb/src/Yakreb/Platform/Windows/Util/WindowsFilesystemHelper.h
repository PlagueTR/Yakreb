#pragma once
#include "Yakreb/Core/Util/FilesystemHelper.h"

namespace Yakreb {

	class WindowsFilesystemHelper : public FilesystemHelper {
		public:
			WindowsFilesystemHelper();

		protected:
			inline virtual std::filesystem::file_time_type GetFileCreationTimeImpl(const std::filesystem::path& path) override;
			inline virtual void SetFileCreationTimeImpl(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) override;

	};

}