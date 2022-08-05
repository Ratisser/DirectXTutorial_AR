#include "FEngineCore.h"

FEngineCore::FEngineCore()
	: window_(nullptr)
{
}

FEngineCore::~FEngineCore()
{
}

void FEngineCore::Initialize(std::string _windowCaption, std::string _windowClassName, float4 _windowPosition, float4 _windowSize)
{
	window_ = std::make_unique<FEngineWindow>();
	window_->Initialize(_windowCaption, _windowCaption, _windowPosition, _windowSize);

	device_ = std::make_unique<FGraphicDevice>();
	device_->InitializeDevice(window_->GetWindowHandle(), window_->GetWindowSize());

}

void FEngineCore::Run()
{
	tempObject_.Init(device_.get());

	window_->Run(&FEngineCore::GameLoop);
	release();
}

void FEngineCore::DrawObject()
{
	tempObject_.Draw(device_.get());
}

void FEngineCore::GameLoop()
{
	FEngineCore::GetInstance()->device_->RenderStart();

	FEngineCore::GetInstance()->DrawObject();

	FEngineCore::GetInstance()->device_->RenderEnd();
}

void FEngineCore::release()
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
	FEngineCore::GetInstance()->Initialize("Test", "Test", { 100.f, 100.f }, { 1280.f, 720.f });
	FEngineCore::GetInstance()->Run();
	return 0;
}