#include "PreCompile.h"
#include "FFileSystem.h"

FFileSystem::FFileSystem()
{
	path_ = std::filesystem::current_path();
}

FFileSystem::~FFileSystem()
{

}

bool FFileSystem::MoveToParent(const std::string& _parentName)
{
	std::filesystem::path path = path_;
	while (path.has_parent_path())
	{
		path = path.parent_path();

		if (path.string() == _parentName)
		{
			path_ = path;
			return true;
		}
	}
	return false;
}
