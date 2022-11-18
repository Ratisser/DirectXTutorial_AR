#include "PreCompile.h"
#include "FSoundManager.h"
#include "FDebug.h"

#include <Windows.h>

FSoundManager* FSoundManager::mInstance = new FSoundManager;
float FSoundManager::mGlobalVolume = 1.0f;

FSoundManager::FSoundManager()
	: mSystem(nullptr)
	, mChannel(nullptr)
{
}

FMOD::Sound* FSoundManager::getSound(const std::string& _name)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = mAllSounds.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = mAllSounds.end();

	if (findIter == endIter)
	{
		FDebug::MsgBoxError("No Sounds. named : " + _name);
		return nullptr;
	}

	return findIter->second;
}

FSoundManager::~FSoundManager()
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator startIter = mAllSounds.begin();
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = mAllSounds.end();

	while (startIter != endIter)
	{
		startIter->second->release();
		++startIter;
	}

	mAllSounds.clear();

	mSystem->close();
	mSystem->release();
}

void FSoundManager::Initialize()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&mSystem);
	if (FMOD_OK != result)
	{
		FDebug::MsgBoxError("FMOD system create failed.");
	}

	result = mSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	if (FMOD_OK != result)
	{
		FDebug::MsgBoxError("FMOD system initialize failed.");
	}
}

void FSoundManager::Update()
{
	if (nullptr == mSystem)
	{
		FDebug::AssertFalse();
	}

	mSystem->update();
}

void FSoundManager::CreateSound(const std::string& _name, const std::string& _path, bool _bLoop)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = mAllSounds.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = mAllSounds.end();

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

	result = mSystem->createSound(_path.c_str(), mode, nullptr, &newSound);

	if (FMOD_OK != result)
	{
		FDebug::MsgBoxError("createSound failed.");
	}

	mAllSounds[_name] = newSound;
}

void FSoundManager::PlaySoundByName(const std::string& _name)
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator findIter = mAllSounds.find(_name);
	std::unordered_map<std::string, FMOD::Sound*>::iterator endIter = mAllSounds.end();

	if (findIter == endIter)
	{
		FDebug::MsgBoxError("No Sounds.");
	}

	mSystem->playSound(findIter->second, 0, false, &mChannel);
	if (mChannel != nullptr)
	{
		FMOD_RESULT result = mChannel->setVolume(FSoundManager::mGlobalVolume);
	}
}

void FSoundManager::SetGlobalVolume(float _volume)
{
	if (_volume <= 1.0f)
	{
		mGlobalVolume = _volume;
	}
	else
	{
		mGlobalVolume = 1.0f;
	}

	//int channels = 0;
	//int realChannels = 0;
	//mSystem->getChannelsPlaying(&channels, &realChannels);

	FMOD::ChannelGroup* cg;
	mSystem->getMasterChannelGroup(&cg);

	int numChannels;
	cg->getNumChannels(&numChannels);

	for (int i = 0; i < numChannels; i++)
	{
		FMOD::Channel* channel = nullptr;
		cg->getChannel(i, &channel);
		if (nullptr != channel)
		{
			channel->setVolume(mGlobalVolume);
		}
	}

	cg->release();
}

void FSoundManager::StopSound()
{
	mChannel->stop();
}

void FSoundManager::Destroy()
{

	if (nullptr != mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}
