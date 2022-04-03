#ifndef _CollisionVolume
#define _CollisionVolume

#include "AzulCore.h"

// forward declaration
class Model;

class CollisionVolumeBSphere;

class CollisionVolume
{
public:
	// big four
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator = (const CollisionVolume&) = delete;
	virtual ~CollisionVolume() = default;

	virtual void ComputeData(Model* mod, const Matrix& mat) = 0;
	//virtual bool Intersect(const CollisionVolume& other) = 0;
	//virtual bool Intersect(const CollisionVolumeBSphere& other) = 0;

private:

};

#endif