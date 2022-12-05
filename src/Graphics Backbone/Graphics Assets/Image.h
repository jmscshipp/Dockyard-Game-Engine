#ifndef _Image
#define _Image

#include "Rect.h"
#include "Texture.h"

class Image
{
public:
	// public methods: -------------------------------------------------------------
	Image();
	Image(Texture* pTexture, Rect* pRect);
	Image(const Image&) = default;
	Image& operator=(const Image&) = default;
	~Image();

	void Set(Texture* pTexture, Rect* pRect);
	Rect* GetRect();
	Texture* GetTexture();

private:
	Rect* rect;
	Texture* tex;
};


#endif