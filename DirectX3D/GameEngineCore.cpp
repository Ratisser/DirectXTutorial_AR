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
	tempObject_.Init(device_.get());

	window_->Run(&GameEngineCore::GameLoop);
	release();
}

void GameEngineCore::DrawObject()
{
	tempObject_.Draw(device_.get());
}

void GameEngineCore::GameLoop()
{

	GameEngineCore::GetInstance()->device_->RenderStart();

	GameEngineCore::GetInstance()->DrawObject();

	GameEngineCore::GetInstance()->device_->RenderEnd();
}

void GameEngineCore::release()
{
	if (device_ != nullptr)
	{
		device_->Release();
	}
}

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameEngineCore::GetInstance()->Initialize("Test", "Test", { 100.f, 100.f }, { 1280.f, 720.f });
	GameEngineCore::GetInstance()->Run();
	return 0;
}