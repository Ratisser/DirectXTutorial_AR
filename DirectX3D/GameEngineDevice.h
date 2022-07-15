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
	void RenderStart();
	void RenderEnd();

	void Release();

	inline ID3D11Device* GetDevice() { return device_; }
	inline ID3D11DeviceContext* GetContext() { return deviceContext_; }

private:
	const float4 CLEAR_COLOR = { 0.0f, 0.0f, 1.0f, 1.0f };

private:
	ID3D11Device* device_;
	ID3D11DeviceContext* deviceContext_;
	IDXGISwapChain* swapChain_;
	D3D_DRIVER_TYPE	driverType_;
	D3D_FEATURE_LEVEL featureLevel_;

	ID3D11RenderTargetView* backBufferTarget_;

public:
	ID3DBlob* vsBlob_ = nullptr;
	ID3DBlob* psBlob_ = nullptr;
	ID3D11VertexShader* vs_;
	ID3D11PixelShader* ps_;
};
