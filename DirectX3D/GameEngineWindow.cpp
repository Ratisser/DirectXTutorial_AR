#include "GameEngineWindow.h"

#include <cassert>

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		break;;
	case WM_CREATE:
		break;
	case WM_QUIT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow::GameEngineWindow()
	: hInstance_(nullptr)
	, hWnd_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow()
{
}

void GameEngineWindow::Initialize(std::string _windowCaption, std::string _windowClassName, float4 _windowPosition, float4 _windowSize)
{
	windowCaption_ = _windowCaption;
	windowClassName_ = _windowClassName;

	windowPosition_ = _windowPosition;
	windowSize_ = _windowSize;

	if (0 != registerWindowClass())
	{
		assert(false);
	}

	if (0 != createWindow())
	{
		assert(false);
	}

}

void GameEngineWindow::Run(void(*_callback)())
{
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (nullptr != _callback)
			{
				_callback();
			}
		}
	}
}

int GameEngineWindow::registerWindowClass()
{
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = nullptr;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = windowClassName_.c_str();
	wcex.hIconSm = nullptr;
	return !RegisterClassExA(&wcex);
}

int GameEngineWindow::createWindow()
{
	hWnd_ = CreateWindowExA(0, windowClassName_.c_str(), windowCaption_.c_str(),
		WS_POPUPWINDOW,
		windowPosition_.ix(), windowPosition_.iy(),
		windowSize_.ix(), windowSize_.iy(),
		nullptr, nullptr, nullptr, nullptr);

	if (nullptr == hWnd_)
	{
		assert(false);
	}

	RECT Rc = { 0, 0, windowSize_.ix(), windowSize_.iy() };
	// 내가 넣어준 렉트에 타이틀바와 메뉴등의 사이즈가 들어간 녀석으로 만들어주세요.
	AdjustWindowRect(&Rc, WS_POPUPWINDOW, false);

	// 0넣으면 그냥 보통 기본이다.
	SetWindowPos(hWnd_, nullptr, windowPosition_.ix(), windowPosition_.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, 0);

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_);

	return 0;
}
