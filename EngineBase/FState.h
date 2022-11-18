#pragma once

#include <functional>
#include <map>

class FState
{
	class State
	{
		friend FState;
	public:
		State(const std::string& _stateName, std::function<void(float)> _start, std::function<void(float)> _update, std::function<void(float)> _end = nullptr);
	private:
		std::string mStateName;
		std::function<void(float)> mStartFunction;
		std::function<void(float)> mUpdateFunction;
		std::function<void(float)> mEndFunction;

		float mElapsedTime;
	};

public:
	FState();
	~FState();
	FState(const FState& _other) = delete;
	FState(FState&& _other) = delete;
	FState& operator=(const FState& _other) = delete;
	FState& operator=(const FState&& _other) = delete;

public:
	inline void operator<<(const std::string& _rhs) { ChangeState(_rhs); }

public:
	void CreateState(const std::string& _stateName, std::function<void(float)> _start, std::function<void(float)> _update, std::function<void(float)> _end = nullptr);

	void ChangeState(const std::string& _stateName);

	void Update(float _deltaTime);

	std::string GetCurrentStateName();
	float GetTime() const;
	void SetTime(float _time);

private:
	std::map<std::string, FState::State*> mAllStates;

	State* mCurrentState;
	State* mNextState;
};

