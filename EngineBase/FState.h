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
		std::string stateName_;
		std::function<void(float)> start_;
		std::function<void(float)> update_;
		std::function<void(float)> end_;

		float elapsedTime_;
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
	std::map<std::string, FState::State*> allState_;

	State* currentState_;
	State* nextState_;
};

