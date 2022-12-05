#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolumeBBBase.h"

class CollisionVolumeOBB : public CollisionVolumeBBBase
{
public:
	// big four
	CollisionVolumeOBB() = default;
	CollisionVolumeOBB(const CollisionVolumeOBB&) = delete;
	CollisionVolumeOBB& operator = (const CollisionVolumeOBB&) = delete;
	virtual ~CollisionVolumeOBB() = default;

	// inherited from collision volume bounding box base class
	void ComputeData(Model* mod, const Matrix& mat) override;
	void DebugView(const Vect& color) const override;
	bool IntersectAccept(const CollisionVolume& other) const override;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	// access private members
	const Vect& GetMin() const override;
	const Vect& GetMax() const override;
	const Matrix& GetWorld() const override;
	const Vect& GetHalfDiagonal() const override;
	const float GetScaleSqrd() const override;
	const Vect& GetCenter() const override;
};

#endif