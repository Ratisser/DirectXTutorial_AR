#pragma once

#include <filesystem>

class FFileSystem
{
public:
	FFileSystem();
	~FFileSystem();

	FFileSystem(const FFileSystem& _other) = delete;
	FFileSystem(FFileSystem&& _other) = delete;

	FFileSystem& operator=(const FFileSystem& _other) = delete;
	FFileSystem& operator=(const FFileSystem&& _other) = delete;

public:
	std::string GetDirectoryName() { return mPath.has_parent_path() ? mPath.parent_path().string() : mPath.string(); };
	std::string GetFileName() { return mPath.has_filename() ? mPath.filename().string() : ""; }

	bool MoveToParent(const std::string& _parentName);

private:
	std::filesystem::path mPath;
};

