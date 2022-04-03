#ifndef _DockyardAttorney
#define _DockyardAttorney

#include "Dockyard.h"

class DockyardAttorney
{
public:
	// big four
	DockyardAttorney() = default;
	DockyardAttorney(const DockyardAttorney&) = delete;
	DockyardAttorney& operator = (const DockyardAttorney&) = delete;
	~DockyardAttorney() = default;

	friend class FreezeTime;

private:
	static float GetTime() { return Dockyard::GetTimeInSeconds(); }
};

#endif