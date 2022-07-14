#include "GameEngineCore.h"

int WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    GameEngineCore::GetInstance()->Initialize("Test", "Test", { 100.f, 100.f }, { 1280.f, 720.f });
    GameEngineCore::GetInstance()->Run();
	return 0;
}