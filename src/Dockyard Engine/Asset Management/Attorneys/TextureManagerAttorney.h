#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"

class TextureManagerAttorney
{
public:
	// big four
	TextureManagerAttorney() = default;
	TextureManagerAttorney(const TextureManagerAttorney&) = delete;
	TextureManagerAttorney& operator = (const TextureManagerAttorney&) = delete;
	~TextureManagerAttorney() = default;

	friend class Dockyard;

private:
	static void Delete() { TextureManager::Delete(); }
};

#endif