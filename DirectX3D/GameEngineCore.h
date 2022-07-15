#pragma once
#include "GameEngineWindow.h"
#include "GameEngineDevice.h"

#include <memory>

#include "Object.hpp"

class GameEngineCore
{
public:
	GameEngineCore();
	virtual ~GameEngineCore();

public:
	static GameEngineCore* GetInstance() { static GameEngineCore instance; return &instance; }

	void Initialize(std::string _windowCaption, std::string _windowClassName, float4 _windowPosition, float4 _windowSize);
	void Run();
	
	void DrawObject();

public:
	GameEngineWindow* GetWindow() { return window_.get(); }

private:
	static void GameLoop();

	void release();

private:
	std::unique_ptr<GameEngineWindow> window_;
	std::unique_ptr<GameEngineDevice> device_;

	Object tempObject_;
};

