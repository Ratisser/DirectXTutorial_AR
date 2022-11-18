#include "PreCompile.h"
#include "FSoundPlayer.h"

FSoundPlayer::FSoundPlayer(const std::string& _soundName)
	: mSound(nullptr)
	, mChannel(nullptr)
	, mVolume(1.0f)
{
	mSound = FSoundManager::GetInstance().getSound(_soundName);
}

FSoundPlayer::~FSoundPlayer()
{
}

void FSoundPlayer::ChangeSound(const std::string& _soundName)
{
	mSound = FSoundManager::GetInstance().getSound(_soundName);
}

void FSoundPlayer::Play()
{
	FSoundManager::GetInstance().mSystem->playSound(mSound, nullptr, false, &mChannel);
	if (mChannel != nullptr)
	{
		FMOD_RESULT result = mChannel->setVolume(FSoundManager::mGlobalVolume * mVolume);
	}
}

void FSoundPlayer::Stop()
{
	FMOD_RESULT result = mChannel->stop();
}

bool FSoundPlayer::IsPlaying()
{
	bool bReturn;
	FMOD_RESULT result = mChannel->isPlaying(&bReturn);
	return bReturn;
}

bool FSoundPlayer::IsPaused()
{
	bool bReturn = true;
	if (mChannel != nullptr)
	{
		FMOD_RESULT result = mChannel->getPaused(&bReturn);
	}
	return bReturn;
}

void FSoundPlayer::SetPaused(bool _bPause)
{
	if (mChannel != nullptr)
	{
		FMOD_RESULT result = mChannel->setPaused(_bPause);
	}
}

void FSoundPlayer::SetVolume(float _volume)
{
	mVolume = _volume;
	if (mChannel != nullptr)
	{
		FMOD_RESULT result = mChannel->setVolume(FSoundManager::mGlobalVolume * mVolume);
	}
}

void FSoundPlayer::SetPitch(float _pitch)
{
	if (mChannel != nullptr)
	{
		FMOD_RESULT result = mChannel->setPitch(_pitch);
	}
}

void FSoundPlayer::SetPosition(unsigned int _positionMilliSec)
{
	if (mChannel != nullptr)
	{
		FMOD_RESULT result = mChannel->setPosition(_positionMilliSec, FMOD_TIMEUNIT_MS);
	}
}

unsigned int FSoundPlayer::GetPositionMillisecond()
{
	unsigned int returnPosition;
	FMOD_RESULT result = mChannel->getPosition(&returnPosition, FMOD_TIMEUNIT_MS);
	return returnPosition;
}

unsigned int FSoundPlayer::GetLengthMillisecond()
{
	unsigned int returnLength;
	FMOD_RESULT result = mSound->getLength(&returnLength, FMOD_TIMEUNIT_MS);
	return returnLength;
}
