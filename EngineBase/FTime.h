#pragma once
#include <Windows.h>
// #include <chrono>

class FTime
{
public:
	FTime();
	~FTime();
	FTime(const FTime& _Other) = delete;
	FTime(const FTime&& _Other) = delete;
	FTime& operator=(const FTime& _Other) = delete;
	FTime& operator=(const FTime&& _Other) = delete;

public:
	static FTime& GetInstance() { static FTime SingletonInstance; return SingletonInstance; }

public:
	double GetDeltaTimeD() { return mDeltaTime; }
	float GetDeltaTime() { return static_cast<float>(mDeltaTime) * mTimeScale; }

public:
	void TimeCheckReset();
	void TimeCheck();
	void SetTimeScale(float _scale);

private:
	LARGE_INTEGER mTimeCount;
	LARGE_INTEGER mStartCheck;
	LARGE_INTEGER mEndCheck;
	double mDeltaTime;
	float mTimeScale;
};

