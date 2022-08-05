#include "PreCompile.h"
#include "FTime.h"

FTime::FTime()
	: timeScale_(1.0f)
{
	TimeCheckReset();
}

FTime::~FTime()
{
}

void FTime::TimeCheckReset()
{
	QueryPerformanceFrequency(&timeCount_);
	QueryPerformanceCounter(&startCheck_);
	QueryPerformanceCounter(&endCheck_);
	timeScale_ = 1.0f;
}

void FTime::TimeCheck()
{
	QueryPerformanceCounter(&endCheck_);
	deltaTime_ = static_cast<double>((endCheck_.QuadPart - startCheck_.QuadPart)) / static_cast<double>(timeCount_.QuadPart);
	startCheck_.QuadPart = endCheck_.QuadPart;
}

void FTime::SetTimeScale(float _scale)
{
	timeScale_ = _scale;
}
