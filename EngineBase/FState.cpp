#include "PreCompile.h"
#include "FState.h"
#include "FDebug.h"

FState::FState()
	: mCurrentState(nullptr)
	, mNextState(nullptr)
{

}

FState::~FState()
{
	for (const std::pair<std::string, FState::State*>& pair : mAllStates)
	{
		delete pair.second;
	}
}


void FState::CreateState(const std::string& _stateName, std::function<void(float)> _start, std::function<void(float)> _update, std::function<void(float)> _end)
{
	std::map<std::string, FState::State*>::iterator findIter = mAllStates.find(_stateName);

	if (findIter != mAllStates.end())
	{
		FDebug::MsgBoxError("state named : [" + _stateName + "] already exists");
	}

	FState::State* newState = new FState::State(_stateName, _start, _update, _end);

	mAllStates.insert(std::pair<std::string, FState::State*>(_stateName, newState));
}

void FState::ChangeState(const std::string& _stateName)
{
	std::map<std::string, FState::State*>::iterator findIter = mAllStates.find(_stateName);

	if (findIter == mAllStates.end())
	{
		FDebug::MsgBoxError("state named : [" + _stateName + "] no exists");
	}

	mNextState = findIter->second;
}

void FState::Update(float _deltaTime)
{
	if (nullptr != mNextState)
	{
		if (nullptr != mCurrentState && nullptr != mCurrentState->mEndFunction)
		{
			mCurrentState->mEndFunction(_deltaTime);
		}
		mNextState->mStartFunction(_deltaTime);
		mCurrentState = mNextState;
		mCurrentState->mElapsedTime = 0.0f;
		mNextState = nullptr;
	}

	if (nullptr != mCurrentState)
	{
		mCurrentState->mElapsedTime += _deltaTime;
		mCurrentState->mUpdateFunction(_deltaTime);
	}
}

FState::State::State(const std::string& _stateName, std::function<void(float)> _start, std::function<void(float)> _update, std::function<void(float)> _end)
	: mStateName(_stateName)
	, mStartFunction(_start)
	, mUpdateFunction(_update)
	, mEndFunction(_end)
	, mElapsedTime(0.0f)
{
}


std::string FState::GetCurrentStateName()
{
	if (nullptr == mCurrentState)
	{
		return std::string();
	}
	else
	{
		return mCurrentState->mStateName;
	}
}

float FState::GetTime() const
{
	if (nullptr != mCurrentState)
	{
		return mCurrentState->mElapsedTime;
	}
	return 0.0f;
}

void FState::SetTime(float _time)
{
	if (nullptr != mCurrentState)
	{
		mCurrentState->mElapsedTime = _time;
	}
}