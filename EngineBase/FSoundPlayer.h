#pragma once

#include "FSoundManager.h"

class FSoundPlayer
{
public:
	// SoundManager �� �ε�� ���常 ����� �� �ֽ��ϴ�.
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

	float GetVolume() const { return volume_; }

private:
	FMOD::Sound* sound_;
	FMOD::Channel* channel_;

	float volume_;
};

