#include "PreCompile.h"
#include "FSoundManager.h"
#include "FDebug.h"

#include <Windows.h>

FSoundManager* FSoundManager::instance_ = new FSoundManager;
float FSoundManager::globalVolume_ = 1.0f;

FSoundManager::FSoundManager()
	: system_(nullptr)
	, channel_(nullptr)
{
}

FMOD::Sound* FSoundManager::getSound(const std::string& _name)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = allSounds_.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	if (findIter == endIter)
	{
		FDebug::MsgBoxError("No Sounds. named : " + _name);
		return nullptr;
	}

	return findIter->second;
}

FSoundManager::~FSoundManager()
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator startIter = allSounds_.begin();
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	while (startIter != endIter)
	{
		startIter->second->release();
		++startIter;
	}

	allSounds_.clear();

	system_->close();
	system_->release();
}

void FSoundManager::Initialize()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&system_);
	if (FMOD_OK != result)
	{
		FDebug::MsgBoxError("FMOD system create failed.");
	}

	result = system_->init(32, FMOD_INIT_NORMAL, nullptr);
	if (FMOD_OK != result)
	{
		FDebug::MsgBoxError("FMOD system initialize failed.");
	}
}

void FSoundManager::Update()
{
	if (nullptr == system_)
	{
		FDebug::AssertFalse();
	}

	system_->update();
}

void FSoundManager::CreateSound(const std::string& _name, const std::string& _path, bool _bLoop)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = allSounds_.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	if (findIter != endIter)
	{
		findIter->second->release();
	}

	FMOD_RESULT result;
	FMOD::Sound* newSound;
	FMOD_MODE mode = FMOD_DEFAULT;

	if (_bLoop)
	{
		mode = FMOD_LOOP_NORMAL;
	}

	result = system_->createSound(_path.c_str(), mode, nullptr, &newSound);

	if (FMOD_OK != result)
	{
		FDebug::MsgBoxError("createSound failed.");
	}

	allSounds_[_name] = newSound;
}

void FSoundManager::PlaySoundByName(const std::string& _name)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = allSounds_.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = allSounds_.end();

	if (findIter == endIter)
	{
		FDebug::MsgBoxError("No Sounds.");
	}

	system_->playSound(findIter->second, 0, false, &channel_);
	if (channel_ != nullptr)
	{
		FMOD_RESULT result = channel_->setVolume(FSoundManager::globalVolume_);
	}
}

void FSoundManager::SetGlobalVolume(float _volume)
{
	if (_volume <= 1.0f)
	{
		globalVolume_ = _volume;
	}
	else
	{
		globalVolume_ = 1.0f;
	}

	//int channels = 0;
	//int realChannels = 0;
	//system_->getChannelsPlaying(&channels, &realChannels);

	FMOD::ChannelGroup* cg;
	system_->getMasterChannelGroup(&cg);

	int numChannels;
	cg->getNumChannels(&numChannels);

	for (int i = 0; i < numChannels; i++)
	{
		FMOD::Channel* channel = nullptr;
		cg->getChannel(i, &channel);
		if (nullptr != channel)
		{
			channel->setVolume(globalVolume_);
		}
	}

	cg->release();
}

void FSoundManager::StopSound()
{
	channel_->stop();
}

void FSoundManager::Destroy()
{

	if (nullptr != instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}
