#ifndef _TerrainManagerAttorney
#define _TerrainManagerAttorney

#include "TerrainManager.h"

class TerrainManagerAttorney
{
public:
	// big four
	TerrainManagerAttorney() = default;
	TerrainManagerAttorney(const TerrainManagerAttorney&) = delete;
	TerrainManagerAttorney& operator = (const TerrainManagerAttorney&) = delete;
	~TerrainManagerAttorney() = default;

	friend class Dockyard;

private:
	static void Delete() { TerrainManager::Delete(); }
};

#endif