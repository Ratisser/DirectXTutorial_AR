#pragma once

#include <vector>
#include "FGraphicDevice.h"
#include <EngineBase/FMath.h>

struct CustomVertex
{
	float4 Position;
};

class Object
{
public:
	Object()
		: vertexBuffer_(nullptr)
		, indexBuffer_(nullptr)
	{
		vertices_.push_back({ float4(-0.5f, 0.0f, 0.0f) });
		vertices_.push_back({ float4(0.0f, 1.0f, 0.0f) });
		vertices_.push_back({ float4(0.5f, 0.0f, 0.0f) });

		indices_.push_back(0);
		indices_.push_back(1);
		indices_.push_back(2);

	}
	~Object()
	{
		vertexBuffer_->Release();
		indexBuffer_->Release();
		inputLayout_->Release();
	}

	void Init(FGraphicDevice* _device)
	{
		if (vertexBuffer_ != nullptr)
		{
			return;
		}

		if (indexBuffer_ != nullptr)
		{
			return;
		}

		D3D11_SUBRESOURCE_DATA InitData;

		D3D11_BUFFER_DESC vertexBufferDesc = { 0, };
		vertexBufferDesc.ByteWidth = vertices_.size() * sizeof(CustomVertex);
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		InitData.pSysMem = &vertices_[0];

		_device->GetDevice()->CreateBuffer(&vertexBufferDesc, &InitData, &vertexBuffer_);

		D3D11_BUFFER_DESC indexBufferDesc = { 0, };
		indexBufferDesc.ByteWidth = indices_.size() * sizeof(int);
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		InitData.pSysMem = &indices_[0];

		_device->GetDevice()->CreateBuffer(&indexBufferDesc, &InitData, &indexBuffer_);


/*
typedef struct D3D11_INPUT_ELEMENT_DESC {
	LPCSTR                     SemanticName;
	UINT                       SemanticIndex;
	DXGI_FORMAT                Format;
	UINT                       InputSlot;
	UINT                       AlignedByteOffset;
	D3D11_INPUT_CLASSIFICATION InputSlotClass;
	UINT                       InstanceDataStepRate;
} D3D11_INPUT_ELEMENT_DESC;
*/
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
		inputElementDesc.push_back({ "Position", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		HRESULT hr = _device->GetDevice()->CreateInputLayout(&inputElementDesc[0], inputElementDesc.size()
			, _device->vsBlob_->GetBufferPointer(), _device->vsBlob_->GetBufferSize(), &inputLayout_);

		if (FAILED(hr))
		{
			assert(false);
		}


	}
	void Draw(FGraphicDevice* _device)
	{
		ID3D11DeviceContext* context = _device->GetContext();


		UINT stride = sizeof(CustomVertex);
		UINT offset = 0;
		_device->GetContext()->IASetInputLayout(inputLayout_);
		_device->GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
		_device->GetContext()->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R32_UINT, 0);
		_device->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		context->VSSetShader(_device->vs_, nullptr, 0);
		context->PSSetShader(_device->ps_, nullptr, 0);

		context->DrawIndexed(indices_.size(), 0, 0);
		


	}

private:
	std::vector<CustomVertex> vertices_;
	std::vector<unsigned int> indices_;


	ID3D11Buffer* vertexBuffer_;
	ID3D11Buffer* indexBuffer_;
	ID3D11InputLayout* inputLayout_;
};