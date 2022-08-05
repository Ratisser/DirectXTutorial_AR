#include "PreCompile.h"
#include "FSoundPlayer.h"

FSoundPlayer::FSoundPlayer(const std::string& _soundName)
	: sound_(nullptr)
	, channel_(nullptr)
	, volume_(1.0f)
{
	sound_ = FSoundManager::GetInstance().getSound(_soundName);
}

FSoundPlayer::~FSoundPlayer()
{
}

void FSoundPlayer::ChangeSound(const std::string& _soundName)
{
	sound_ = FSoundManager::GetInstance().getSound(_soundName);
}

void FSoundPlayer::Play()
{
	FSoundManager::GetInstance().system_->playSound(sound_, nullptr, false, &channel_);
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setVolume(FSoundManager::globalVolume_ * volume_);
	}
}

void FSoundPlayer::Stop()
{
	FMOD_RESULT result = channel_->stop();
}

bool FSoundPlayer::IsPlaying()
{
	bool bReturn;
	FMOD_RESULT result = channel_->isPlaying(&bReturn);
	return bReturn;
}

bool FSoundPlayer::IsPaused()
{
	bool bReturn = true;
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->getPaused(&bReturn);
	}
	return bReturn;
}

void FSoundPlayer::SetPaused(bool _bPause)
{
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setPaused(_bPause);
	}
}

void FSoundPlayer::SetVolume(float _volume)
{
	volume_ = _volume;
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setVolume(FSoundManager::globalVolume_ * volume_);
	}
}

void FSoundPlayer::SetPitch(float _pitch)
{
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setPitch(_pitch);
	}
}

void FSoundPlayer::SetPosition(unsigned int _positionMilliSec)
{
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setPosition(_positionMilliSec, FMOD_TIMEUNIT_MS);
	}
}

unsigned int FSoundPlayer::GetPositionMillisecond()
{
	unsigned int returnPosition;
	FMOD_RESULT result = channel_->getPosition(&returnPosition, FMOD_TIMEUNIT_MS);
	return returnPosition;
}

unsigned int FSoundPlayer::GetLengthMillisecond()
{
	unsigned int returnLength;
	FMOD_RESULT result = sound_->getLength(&returnLength, FMOD_TIMEUNIT_MS);
	return returnLength;
}
