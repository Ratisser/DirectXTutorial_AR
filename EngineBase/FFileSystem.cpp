#include "PreCompile.h"
#include "FFileSystem.h"

FFileSystem::FFileSystem()
{
	mPath = std::filesystem::current_path();
}

FFileSystem::~FFileSystem()
{

}

bool FFileSystem::MoveToParent(const std::string& _parentName)
{
	std::filesystem::path path = mPath;
	while (path.has_parent_path())
	{
		path = path.parent_path();

		if (path.string() == _parentName)
		{
			mPath = path;
			return true;
		}
	}
	return false;
}
