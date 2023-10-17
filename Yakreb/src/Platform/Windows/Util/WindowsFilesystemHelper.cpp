#include "yakrebpch.h"
#include "WindowsFilesystemHelper.h"

namespace Yakreb {

	void WindowsFilesystemHelper::Init() {
		wchar_t buffer[MAX_PATH];
		GetModuleFileNameW(NULL, buffer, MAX_PATH);
		s_ExecutablePath = std::filesystem::canonical(buffer);
		s_ExecutableDirectoryPath = s_ExecutablePath.parent_path();
		s_ExecutableName = s_ExecutablePath.filename().string();
	}

	std::filesystem::file_time_type FilesystemHelper::GetFileCreationTime(const std::filesystem::path& path) {
		HANDLE fileHandle = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		FILETIME creationTime = { 0 };
		if (fileHandle != INVALID_HANDLE_VALUE) {
			GetFileTime(fileHandle, &creationTime, NULL, NULL);
			CloseHandle(fileHandle);
		}
		
		FILETIME localCreationTime = { 0 };
		FileTimeToLocalFileTime(&creationTime, &localCreationTime);

		SYSTEMTIME systemTime = { 0 };
		FileTimeToSystemTime(&localCreationTime, &systemTime);

		std::tm timeInfo = { 0 };
		timeInfo.tm_year = systemTime.wYear - 1900;
		timeInfo.tm_mon = systemTime.wMonth - 1;
		timeInfo.tm_mday = systemTime.wDay;
		timeInfo.tm_hour = systemTime.wHour;
		timeInfo.tm_min = systemTime.wMinute;
		timeInfo.tm_sec = systemTime.wSecond;
		timeInfo.tm_isdst = -1;
		
		time_t time = std::mktime(&timeInfo);

		std::chrono::seconds secs(time);

		return std::filesystem::file_time_type(std::chrono::duration_cast<std::chrono::system_clock::duration>(secs));
	}

	void FilesystemHelper::SetFileCreationTime(const std::filesystem::path& path, const std::filesystem::file_time_type& creationTime) {

		std::chrono::system_clock::time_point timePoint(std::chrono::duration_cast<std::chrono::seconds>(creationTime.time_since_epoch()));

		time_t time = std::chrono::system_clock::to_time_t(timePoint);

		std::tm *timeInfo = std::localtime(&time);

		SYSTEMTIME systemTime = { 0 };
		systemTime.wYear = timeInfo->tm_year + 1900;
		systemTime.wMonth = timeInfo->tm_mon + 1;
		systemTime.wDay = timeInfo->tm_mday;
		systemTime.wHour = timeInfo->tm_hour;
		systemTime.wMinute = timeInfo->tm_min;
		systemTime.wSecond = timeInfo->tm_sec;

		FILETIME fileCreationTime = { 0 };
		SystemTimeToFileTime(&systemTime, &fileCreationTime);

		HANDLE fileHandle = CreateFile(path.c_str(), FILE_WRITE_ATTRIBUTES, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (fileHandle != INVALID_HANDLE_VALUE) {
			SetFileTime(fileHandle, &fileCreationTime, nullptr, nullptr);
			CloseHandle(fileHandle);
		}

	}

}