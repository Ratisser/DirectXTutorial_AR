#pragma once

#include "FSoundManager.h"

class FSoundPlayer
{
public:
	// SoundManager 에 로드된 사운드만 재생할 수 있습니다.
	FSoundPlayer(const std::string& _soundName);
	~FSoundPlayer();
	FSoundPlayer(const FSoundPlayer& _other) = delete;
	FSoundPlayer(FSoundPlayer&& _other) = delete;
	FSoundPlayer& operator=(const FSoundPlayer& _other) = delete;
	FSoundPlayer& operator=(const FSoundPlayer&& _other) = delete;

public:
	void ChangeSound(const std::string& _soundName);

	void Play();
	void Stop();

	bool IsPlaying();
	bool IsPaused();
	void SetPaused(bool _bPause);
	void SetVolume(float _volume);
	void SetPitch(float _pitch);
	void SetPosition(unsigned int _positionMilliSec);
	unsigned int GetPositionMillisecond();
	unsigned int GetLengthMillisecond();

	float GetVolume() const { return mVolume; }

private:
	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;

	float mVolume;
};

