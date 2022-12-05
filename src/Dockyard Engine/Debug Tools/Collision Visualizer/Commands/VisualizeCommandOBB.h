#ifndef _VisualizeCommandOBB
#define _VisualizeCommandOBB

#include "VisualizeCommandBase.h"
#include "Vect.h"

// forward declaration
class CollisionVolumeOBB;

class VisualizeCommandOBB : public VisualizeCommandBase
{
public:
	// big four
	VisualizeCommandOBB() = default;
	VisualizeCommandOBB(const VisualizeCommandOBB&) = delete;
	VisualizeCommandOBB& operator = (const VisualizeCommandOBB&) = delete;
	~VisualizeCommandOBB() = default;

	void Initialize(const CollisionVolumeOBB& box, const Vect& color);
	void Execute(VisualizeCommandPool* pool) override;

private:
	const CollisionVolumeOBB* colVolume;
	const Vect* displayColor;
};

#endif