#pragma once

#include <Windows.h>
#include <string>
#include <EngineBase\FMath.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


class FEngineWindow
{
public:
	FEngineWindow();
	~FEngineWindow();

public:
	//static GameEngineWindow* GetInstance() { static GameEngineWindow intstance; return &intstance; }

public:
	void Initialize(std::string _windowCaption, std::string _windowClassName, float4 _windowPosition, float4 _windowSize);
	void Run(void(*_callback)() = nullptr);

	HWND GetWindowHandle() { return hWnd_; }
	float4 GetWindowPosition() { return windowPosition_; }
	float4 GetWindowSize() { return windowSize_; }

private:
	int registerWindowClass();
	int createWindow();

private:
	std::string windowCaption_;
	std::string windowClassName_;

	float4 windowPosition_;
	float4 windowSize_;

	HWND hWnd_;
	HINSTANCE hInstance_;
};

