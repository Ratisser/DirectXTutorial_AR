#include "PreCompile.h"
#include "FTime.h"

FTime::FTime()
	: mTimeScale(1.0f)
{
	TimeCheckReset();
}

FTime::~FTime()
{
}

void FTime::TimeCheckReset()
{
	QueryPerformanceFrequency(&mTimeCount);
	QueryPerformanceCounter(&mStartCheck);
	QueryPerformanceCounter(&mEndCheck);
	mTimeScale = 1.0f;
}

void FTime::TimeCheck()
{
	QueryPerformanceCounter(&mEndCheck);
	mDeltaTime = static_cast<double>((mEndCheck.QuadPart - mStartCheck.QuadPart)) / static_cast<double>(mTimeCount.QuadPart);
	mStartCheck.QuadPart = mEndCheck.QuadPart;
}

void FTime::SetTimeScale(float _scale)
{
	mTimeScale = _scale;
}
