#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolumeBBBase.h"
#include <list>

class CollisionVolumeAABB : public CollisionVolumeBBBase
{
public:
	// big four
	CollisionVolumeAABB() = default;
	CollisionVolumeAABB(const CollisionVolumeAABB&) = delete;
	CollisionVolumeAABB& operator = (const CollisionVolumeAABB&) = delete;
	virtual ~CollisionVolumeAABB() = default;

	// inherited from collision volume bounding box base class
	void ComputeData(Model* mod, const Matrix& mat) override;
	void ComputeData(const Vect& min, const Vect& max); // special overload for collision group AABBs
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