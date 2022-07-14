#pragma once

#include <DirectXPackedVector.h>

#include <Windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>

#include "GameEngineMath.h"

#pragma comment(lib, "D3D11.lib")

class GameEngineDevice
{
public:
	GameEngineDevice();
	~GameEngineDevice();

public:
	//static GameEngineDevice* GetInstance() { static GameEngineDevice instance; return &instance; }
	
public:
	bool InitializeDevice(HWND _hWnd, float4 _size);
	void Render();

	void Release();

private:
	const float4 CLEAR_COLOR = { 0.0f, 0.0f, 1.0f, 1.0f };

private:
	ID3D11Device* device_;
	ID3D11DeviceContext* deviceContext_;
	IDXGISwapChain* swapChain_;
	D3D_DRIVER_TYPE	driverType_;
	D3D_FEATURE_LEVEL featureLevel_;

	ID3D11RenderTargetView* backBufferTarget_;


};
