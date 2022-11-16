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
	std::string GetDirectoryName() { return path_.has_parent_path() ? path_.parent_path().string() : path_.string(); };
	std::string GetFileName() { return path_.has_filename() ? path_.filename().string() : ""; }

	bool MoveToParent(const std::string& _parentName);

private:
	std::filesystem::path path_;
};

