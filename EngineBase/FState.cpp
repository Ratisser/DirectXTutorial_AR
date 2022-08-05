#include "PreCompile.h"
#include "FState.h"
#include "FDebug.h"

FState::FState()
	: currentState_(nullptr)
	, nextState_(nullptr)
{

}

FState::~FState()
{
	for (const std::pair<std::string, FState::State*>& pair : allState_)
	{
		delete pair.second;
	}
}


void FState::CreateState(const std::string& _stateName, std::function<void(float)> _start, std::function<void(float)> _update, std::function<void(float)> _end)
{
	std::map<std::string, FState::State*>::iterator findIter = allState_.find(_stateName);

	if (findIter != allState_.end())
	{
		FDebug::MsgBoxError("state named : [" + _stateName + "] already exists");
	}

	FState::State* newState = new FState::State(_stateName, _start, _update, _end);

	allState_.insert(std::pair<std::string, FState::State*>(_stateName, newState));
}

void FState::ChangeState(const std::string& _stateName)
{
	std::map<std::string, FState::State*>::iterator findIter = allState_.find(_stateName);

	if (findIter == allState_.end())
	{
		FDebug::MsgBoxError("state named : [" + _stateName + "] no exists");
	}

	nextState_ = findIter->second;
}

void FState::Update(float _deltaTime)
{
	if (nullptr != nextState_)
	{
		if (nullptr != currentState_ && nullptr != currentState_->end_)
		{
			currentState_->end_(_deltaTime);
		}
		nextState_->start_(_deltaTime);
		currentState_ = nextState_;
		currentState_->elapsedTime_ = 0.0f;
		nextState_ = nullptr;
	}

	if (nullptr != currentState_)
	{
		currentState_->elapsedTime_ += _deltaTime;
		currentState_->update_(_deltaTime);
	}
}

FState::State::State(const std::string& _stateName, std::function<void(float)> _start, std::function<void(float)> _update, std::function<void(float)> _end)
	: stateName_(_stateName)
	, start_(_start)
	, update_(_update)
	, end_(_end)
	, elapsedTime_(0.0f)
{
}


std::string FState::GetCurrentStateName()
{
	if (nullptr == currentState_)
	{
		return std::string();
	}
	else
	{
		return currentState_->stateName_;
	}
}

float FState::GetTime() const
{
	if (nullptr != currentState_)
	{
		return currentState_->elapsedTime_;
	}
	return 0.0f;
}

void FState::SetTime(float _time)
{
	if (nullptr != currentState_)
	{
		currentState_->elapsedTime_ = _time;
	}
}