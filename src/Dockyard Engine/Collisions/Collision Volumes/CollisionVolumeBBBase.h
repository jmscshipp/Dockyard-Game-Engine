#ifndef _CollisionVolumeBBBase
#define _CollisionVolumeBBBase

#include "CollisionVolume.h"
#include "Matrix.h"

class CollisionVolumeBBBase : public CollisionVolume, public Align16
{
public:
	// big four
	CollisionVolumeBBBase() = default;
	CollisionVolumeBBBase(const CollisionVolumeBBBase&) = delete;
	CollisionVolumeBBBase& operator = (const CollisionVolumeBBBase&) = delete;
	virtual ~CollisionVolumeBBBase() = default;

	// inherited from collision volume base class
	virtual void ComputeData(Model* mod, const Matrix& mat) = 0;
	virtual void DebugView(const Vect& color) const = 0;
	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;

	// access private members
	virtual const Vect& GetMin() const = 0;
	virtual const Vect& GetMax() const = 0;
	virtual const Matrix& GetWorld() const = 0;
	virtual const Vect& GetHalfDiagonal() const = 0;
	virtual const float GetScaleSqrd() const = 0;
	virtual const Vect& GetCenter() const = 0;

protected:
	Vect min, max; // model space for OBB, world space for AABB
	Vect halfDiagonal;
	Matrix world;
	Vect center;
	float scaleSqrd;
};

#endif