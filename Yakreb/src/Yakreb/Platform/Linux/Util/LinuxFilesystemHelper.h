#pragma once
#include "Yakreb/Core/Util/FilesystemHelper.h"

namespace Yakreb {

	class LinuxFilesystemHelper : public FilesystemHelper {
		public:
			LinuxFilesystemHelper();

		protected:
			inline virtual std::filesystem::file_time_type GetFileCreationTimeImpl(const std::filesystem::path& path) override;
			inline virtual void SetFileCreationTimeImpl(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) override;

	};

}