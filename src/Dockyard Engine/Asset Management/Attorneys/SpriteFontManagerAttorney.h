#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h"

class SpriteFontManagerAttorney
{
public:
	// big four
	SpriteFontManagerAttorney() = default;
	SpriteFontManagerAttorney(const SpriteFontManagerAttorney&) = delete;
	SpriteFontManagerAttorney& operator = (const SpriteFontManagerAttorney&) = delete;
	~SpriteFontManagerAttorney() = default;

	friend class Dockyard;

private:
	static void Delete() { SpriteFontManager::Delete(); }
};

#endif