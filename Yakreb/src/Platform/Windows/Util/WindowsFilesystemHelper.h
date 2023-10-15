#pragma once
#include "Yakreb/Core/Util/FilesystemHelper.h"

namespace Yakreb {

	class WindowsFilesystemHelper : public FilesystemHelper {
		private:
			static void Init();

			static std::filesystem::file_time_type GetFileCreationTime(const std::filesystem::path& path);
			static void SetFileCreationTime(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime);

			friend void FilesystemHelper::Init();
			friend std::filesystem::file_time_type FilesystemHelper::GetFileCreationTime(const std::filesystem::path&);
			friend void FilesystemHelper::SetFileCreationTime(const std::filesystem::path&, const std::filesystem::file_time_type&);

	};

}