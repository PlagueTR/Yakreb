#pragma once
#include "Yakreb/Core/Util/FilesystemHelper.h"

namespace Yakreb {

	class LinuxFilesystemHelper : public FilesystemHelper {
		private:
			static void Init();

			static std::filesystem::file_time_type GetFileCreationTime(const std::filesystem::path& path);
			// Can not modify file creation date on Linux without system specific utilities or libraries such as debugfs
			//static void SetFileCreationTime(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime);

			friend void FilesystemHelper::Init();
			friend std::filesystem::file_time_type FilesystemHelper::GetFileCreationTime(const std::filesystem::path&);

	};

}