#include "Image.h"

Image::Image()
	: rect(nullptr), tex(nullptr)
{
}

Image::Image(Texture* pTexture, Rect* pRect)
	: rect(pRect), tex(pTexture)
{
}

Image::~Image()
{
	delete rect;
}

void Image::Set(Texture* pTexture, Rect* pRect)
{
	tex = pTexture;
	rect = pRect;
}

Rect* Image::GetRect()
{
	return rect;
}

Texture* Image::GetTexture()
{
	return tex;
}