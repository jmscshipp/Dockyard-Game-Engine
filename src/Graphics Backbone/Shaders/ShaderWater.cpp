#include "ShaderWater.h"
#include <d3d11.h>
#include <assert.h>
#include "TimeManager.h"
#include "Texture.h"
#include "TimeManager.h"

ShaderWater::ShaderWater()
	: Shader(L"../Assets/Shaders/Water.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// data buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldColorSize);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWorldColorSize);
	assert(SUCCEEDED(hr));
}

ShaderWater::~ShaderWater()
{
	ReleaseAndDeleteCOMobject(mpBuffWorldColorSize);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
}

void ShaderWater::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderWater::SendWorldColorSize(const Matrix& world, const Vect& col, float size)
{
	Data_WorldColorSize wcs;
	wcs.World = world;
	wcs.Color = col;
	wcs.OutlineSize = TimeManager::GetTime();

	this->GetContext()->UpdateSubresource(mpBuffWorldColorSize, 0, nullptr, &wcs, 0, 0);
}

void ShaderWater::SetToContext(ID3D11DeviceContext* devcon)
{
	Shader::SetContext(devcon);
	Shader::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBuffWorldColorSize);
}

void ShaderWater::SetTextureResourceAndSampler(Texture* tex)
{
	tex->SetToContext(this->GetContext(), 0, 0);
}