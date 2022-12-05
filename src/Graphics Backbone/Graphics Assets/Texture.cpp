#include "Texture.h"
#include "DirectXTex.h"
#include <assert.h>
#include "GraphicsUtility.h"
#include "GPUController.h"

Texture::~Texture()
{
	ReleaseAndDeleteCOMobject(mpTextureRV);
	ReleaseAndDeleteCOMobject(mpSampler);
}

Texture::Texture(LPCWSTR filepath, D3D11_FILTER filter, UINT isotropic_level, bool ComputeMip, size_t miplevel, DirectX::TEX_FILTER_FLAGS filterflags )
{
	ID3D11Device* d3dDev = GPUController::GetDevice();

	std::wstring fpath(filepath);
	std::wstring ext = fpath.substr(fpath.find_last_of(L".") + 1);

	DirectX::ScratchImage scrtTex;

	HRESULT hr = S_OK;
	if (ext == L"tga" || ext == L"TGA")
	{
		hr = LoadFromTGAFile(filepath, nullptr, scrtTex);
	} 
	else if (ext == L"dds" || ext == L"DDS")
	{
		hr = LoadFromDDSFile((LPCWSTR)filepath, DirectX::DDS_FLAGS_NONE, nullptr, scrtTex);
	}
	else
	{
		assert(false && "ERROR: Invalid file format");
	}
	assert(SUCCEEDED(hr));

	// computer mipmaps
	if (ComputeMip)
	{
		assert( scrtTex.GetImageCount() == 1 && "ERROR: File already contains MIP map." );
		DirectX::ScratchImage mipchain;
		hr = DirectX::GenerateMipMaps(*(scrtTex.GetImage(0, 0, 0)), filterflags, miplevel, mipchain);
		assert(SUCCEEDED(hr));

		CreateShaderResourceView(d3dDev, mipchain.GetImage(0, 0, 0), mipchain.GetImageCount(), mipchain.GetMetadata(), &mpTextureRV);
	}
	else
	{
		CreateShaderResourceView(d3dDev, scrtTex.GetImage(0, 0, 0), scrtTex.GetImageCount(), scrtTex.GetMetadata(), &mpTextureRV);
	}
	
	// get width and height
	width = scrtTex.GetImages()->width;
	height = scrtTex.GetImages()->height;

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = filter;
	sampDesc.MaxAnisotropy = isotropic_level;		
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = d3dDev->CreateSamplerState(&sampDesc, &mpSampler);
	assert(SUCCEEDED(hr));
}

void Texture::SetToContext(ID3D11DeviceContext* devcon, int texResSlot,  int sampSlot)
{
	devcon->PSSetShaderResources(texResSlot, 1, &mpTextureRV);
	devcon->PSSetSamplers(sampSlot, 1, &mpSampler);
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}