#ifndef _VisualizeCommandAABB
#define _VisualizeCommandAABB

#include "VisualizeCommandBase.h"
#include "Vect.h"

// forward declaration
class CollisionVolumeAABB;

class VisualizeCommandAABB : public VisualizeCommandBase
{
public:
	// big four
	VisualizeCommandAABB() = default;
	VisualizeCommandAABB(const VisualizeCommandAABB&) = delete;
	VisualizeCommandAABB& operator = (const VisualizeCommandAABB&) = delete;
	~VisualizeCommandAABB() = default;

	void Initialize(const CollisionVolumeAABB& box, const Vect& color);
	void Execute(VisualizeCommandPool* pool) override;

private:
	const CollisionVolumeAABB* colVolume;
	const Vect* displayColor;
};

#endif