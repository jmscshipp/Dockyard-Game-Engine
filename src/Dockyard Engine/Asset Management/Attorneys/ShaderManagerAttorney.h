#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{
public:
	// big four
	ShaderManagerAttorney() = default;
	ShaderManagerAttorney(const ShaderManagerAttorney&) = delete;
	ShaderManagerAttorney& operator = (const ShaderManagerAttorney&) = delete;
	~ShaderManagerAttorney() = default;

	friend class Dockyard;

private:
	static void Delete() { ShaderManager::Delete(); }
};

#endif