#pragma once
#include "Yakreb/Core/Util/FilesystemHelper.h"

namespace Yakreb {

	class WindowsFilesystemHelper : public FilesystemHelper {
		public:
			WindowsFilesystemHelper();

		protected:
			virtual inline std::filesystem::file_time_type GetFileCreationTimeImpl(const std::filesystem::path& path) override;
			virtual inline void SetFileCreationTimeImpl(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) override;

	};

}