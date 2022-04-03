#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"

// forward declaration

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
	//bool Intersect(const CollisionVolume& other) override;
	//bool Intersect(const CollisionVolumeBSphere& other) override;

	// access private members
	const Vect& GetCenter() const;
	float GetRadius() const;

private:
	Vect center;
	float radius;
};

#endif