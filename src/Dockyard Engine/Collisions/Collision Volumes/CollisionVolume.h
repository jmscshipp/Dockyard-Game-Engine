#ifndef _CollisionVolume
#define _CollisionVolume

#include "Vect.h"

// forward declaration
class Model;

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume
{
public:
	// big four
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator = (const CollisionVolume&) = delete;
	virtual ~CollisionVolume() = default;

	virtual void ComputeData(Model* mod, const Matrix& mat) = 0;
	virtual void DebugView(const Vect& color) const = 0;
	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;

private:

};

#endif