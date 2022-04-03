#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"

class ModelManagerAttorney
{
public:
	// big four
	ModelManagerAttorney() = default;
	ModelManagerAttorney(const ModelManagerAttorney&) = delete;
	ModelManagerAttorney& operator = (const ModelManagerAttorney&) = delete;
	~ModelManagerAttorney() = default;

	friend class Dockyard;

private:
	static void Delete() { ModelManager::Delete(); }
};

#endif