#ifndef _VisualizeCommandBSphere
#define _VisualizeCommandBSphere

#include "VisualizeCommandBase.h"
#include "Vect.h"

// forward declaration
class CollisionVolumeBSphere;

class VisualizeCommandBSphere : public VisualizeCommandBase
{
public:
	// big four
	VisualizeCommandBSphere() = default;
	VisualizeCommandBSphere(const VisualizeCommandBSphere&) = delete;
	VisualizeCommandBSphere& operator = (const VisualizeCommandBSphere&) = delete;
	~VisualizeCommandBSphere() = default;

	void Initialize(const CollisionVolumeBSphere& sphere, const Vect& color);
	void Execute(VisualizeCommandPool* pool) override;

private:
	const CollisionVolumeBSphere* colSphere;
	const Vect* displayColor;
};

#endif