#include "GameEngineCore.h"

GameEngineCore::GameEngineCore()
	: window_(nullptr)
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::Initialize(std::string _windowCaption, std::string _windowClassName, float4 _windowPosition, float4 _windowSize)
{
	window_ = std::make_unique<GameEngineWindow>();
	window_->Initialize(_windowCaption, _windowCaption, _windowPosition, _windowSize);

	device_ = std::make_unique<GameEngineDevice>();
	device_->InitializeDevice(window_->GetWindowHandle(), window_->GetWindowSize());

}

void GameEngineCore::Run()
{
	window_->Run(&GameEngineCore::GameLoop);

	release();
}

void GameEngineCore::GameLoop()
{
	GameEngineCore::GetInstance()->device_->Render();
}

void GameEngineCore::release()
{
	if (device_ != nullptr)
	{
		device_->Release();
	}
}
