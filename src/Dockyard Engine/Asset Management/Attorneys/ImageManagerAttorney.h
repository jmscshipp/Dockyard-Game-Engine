#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"

class ImageManagerAttorney
{
public:
	// big four
	ImageManagerAttorney() = default;
	ImageManagerAttorney(const ImageManagerAttorney&) = delete;
	ImageManagerAttorney& operator = (const ImageManagerAttorney&) = delete;
	~ImageManagerAttorney() = default;

	friend class Dockyard;

private:
	static void Delete() { ImageManager::Delete(); }
};

#endif