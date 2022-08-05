#include "FGraphicDevice.h"

#include <d3dcompiler.h>
#include "Object.hpp"

#pragma comment(lib, "d3dcompiler.lib")

FGraphicDevice::FGraphicDevice()
	: device_(nullptr)
	, deviceContext_(nullptr)
	, backBufferTarget_(nullptr)
	, swapChain_(nullptr)
	, driverType_(D3D_DRIVER_TYPE_NULL)
	, featureLevel_(D3D_FEATURE_LEVEL_11_0)
{
}

FGraphicDevice::~FGraphicDevice()
{
}

bool FGraphicDevice::InitializeDevice(HWND _hWnd, float4 _size)
{
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
	sd.OutputWindow = _hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		driverType_ = driverTypes[driverTypeIndex];

		hr = D3D11CreateDeviceAndSwapChain(NULL, driverType_, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &swapChain_, &device_, &featureLevel_, &deviceContext_);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	if (FAILED(hr))
	{
		return false;
	}

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	hr = device_->CreateRenderTargetView(pBackBuffer, nullptr, &backBufferTarget_);
	pBackBuffer->Release();
	if (FAILED(hr))
	{
		return false;
	}

	deviceContext_->ClearRenderTargetView(backBufferTarget_, reinterpret_cast<const float*>(&CLEAR_COLOR));
	deviceContext_->OMSetRenderTargets(1, &backBufferTarget_, nullptr);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	deviceContext_->RSSetViewports(1, &vp);

	// 셰이더

	

	// 바이트파일 컴파일?
	hr = D3DCompileFromFile(L"Shader.fx", nullptr, nullptr, "VS", "vs_5_0", D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &vsBlob_, nullptr);
	if (FAILED(hr))
	{
		assert(false);
	}

	device_->CreateVertexShader(vsBlob_->GetBufferPointer(), vsBlob_->GetBufferSize(), nullptr, &vs_);


	hr = D3DCompileFromFile(L"Shader.fx", nullptr, nullptr, "PS", "ps_5_0", D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &psBlob_, nullptr);
	if (FAILED(hr))
	{
		assert(false);
	}

	device_->CreatePixelShader(psBlob_->GetBufferPointer(), psBlob_->GetBufferSize(), nullptr, &ps_);

	deviceContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

void FGraphicDevice::RenderStart()
{
	deviceContext_->OMSetRenderTargets(1, &backBufferTarget_, nullptr);

	deviceContext_->ClearRenderTargetView(backBufferTarget_, reinterpret_cast<const float*>(&CLEAR_COLOR));
}

void FGraphicDevice::RenderEnd()
{
	swapChain_->Present(0, 0);

}

void FGraphicDevice::Release()
{
	vsBlob_->Release();
	vsBlob_ = nullptr;

	psBlob_->Release();
	psBlob_ = nullptr;

	vs_->Release();
	ps_->Release();

	if (nullptr != backBufferTarget_)
	{
		backBufferTarget_->Release();
		backBufferTarget_ = nullptr;
	}

	if (nullptr != swapChain_)
	{
		swapChain_->Release();
		swapChain_ = nullptr;
	}

	if (nullptr != deviceContext_)
	{
		deviceContext_->Release();
		deviceContext_ = nullptr;
	}

	if (nullptr != device_)
	{
		device_->Release();
		device_ = nullptr;
	}

}
