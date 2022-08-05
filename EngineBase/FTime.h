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
	double GetDeltaTimeD() { return deltaTime_; }
	float GetDeltaTime() { return static_cast<float>(deltaTime_) * timeScale_; }

public:
	void TimeCheckReset();
	void TimeCheck();
	void SetTimeScale(float _scale);

private:
	LARGE_INTEGER timeCount_;
	LARGE_INTEGER startCheck_;
	LARGE_INTEGER endCheck_;
	double deltaTime_;
	float timeScale_;
};

