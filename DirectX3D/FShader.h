#pragma once

#include "FGraphicDevice.h"

class FShader
{
public:
	FShader(); 
	~FShader();

	FShader(const FShader& _other) = delete; 
	FShader(FShader&& _other) = delete; 

	FShader& operator=(const FShader& _other) = delete;
	FShader& operator=(const FShader&& _other) = delete;

private:
	ID3DBlob* vsBlob_ = nullptr;
	ID3DBlob* psBlob_ = nullptr;
	ID3D11VertexShader* vs_;
	ID3D11PixelShader* ps_;
};

