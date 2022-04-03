#ifndef _ScreenLogAttorney
#define _ScreenLogAttorney

#include "ScreenLog.h"

class ScreenLogAttorney
{
public:
	// big four
	ScreenLogAttorney() = default;
	ScreenLogAttorney(const ScreenLogAttorney&) = delete;
	ScreenLogAttorney& operator = (const ScreenLogAttorney&) = delete;
	~ScreenLogAttorney() = default;

	// system
	friend class Dockyard;
private:
	static void Render() { ScreenLog::Render(); }
	static void Delete() { ScreenLog::Delete(); }
};

#endif