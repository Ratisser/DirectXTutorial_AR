#include "PreCompile.h"
#include "FDebug.h"


FDebug::FDebug()
{
}

FDebug::~FDebug()
{
}

void FDebug::SetMemoryLeakCheckFlag()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

