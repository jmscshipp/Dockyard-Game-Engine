#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"
#include "Matrix.h"

class CollisionVolumeBSphere : public CollisionVolume, public Align16
{
public:
	// big four
	CollisionVolumeBSphere() = default;
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = delete;
	CollisionVolumeBSphere& operator = (const CollisionVolumeBSphere&) = delete;
	virtual ~CollisionVolumeBSphere() = default;

	// inherited from collision volume base class
	void ComputeData(Model* mod, const Matrix& mat) override;
	void DebugView(const Vect& color) const override;
	bool IntersectAccept(const CollisionVolume& other) const override;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	// access private members
	const Vect& GetCenter() const;
	float GetRadius() const;
	const Vect& GetMin() const;
	const Vect& GetMax() const;

private:
	Vect center;
	float radius;
	Vect min, max;
};

#endif