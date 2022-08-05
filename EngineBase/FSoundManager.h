#pragma once



#pragma warning(push)
#pragma warning(disable:26812)
#include "..\ThirdParty\Include\FMOD\fmod.hpp"
#pragma warning(pop)

#ifdef _DEBUG
#pragma comment(lib, "../ThirdParty/x64/Debug/FMOD/fmodL_vc.lib")
#else
#pragma comment(lib, "../ThirdParty/x64/Release/FMOD/fmod_vc.lib")
#endif


#include <unordered_map>

class FSoundPlayer;
class FSoundManager
{
	friend FSoundPlayer;
public:
	~FSoundManager();

	FSoundManager(const FSoundManager& _other) = delete;
	FSoundManager(FSoundManager&& _other) = delete;

	FSoundManager& operator=(const FSoundManager& _other) = delete;
	FSoundManager& operator=(const FSoundManager&& _other) = delete;

public:
	static FSoundManager& GetInstance() { return *instance_; }
	static void Destroy();

	void Initialize();
	void Update();

	void CreateSound(const std::string& _name, const std::string& _path, bool _bLoop = false);

	void PlaySoundByName(const std::string& _name);
	void SetGlobalVolume(float _volume);
	void StopSound();

	float GetGlobalVolume() const { return globalVolume_; }

private:
	FSoundManager();

	FMOD::Sound* getSound(const std::string& _name);

private:
	static FSoundManager* instance_;
	static float globalVolume_;

private:
	FMOD::System* system_;
	FMOD::Channel* channel_;

	std::unordered_map<std::string, FMOD::Sound*> allSounds_;
};

