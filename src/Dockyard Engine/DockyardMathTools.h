#ifndef _DockyardMathTools
#define _DockyardMathTools

#include "AzulCore.h"
#include "CollisionVolumeBSphere.h"

namespace MathFunctions
{
	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
	{
		float centerDistance = (A.GetCenter() - B.GetCenter()).mag();
		float radiusSum = A.GetRadius() + B.GetRadius();
		if (radiusSum > centerDistance)
			return true;
		return false;
	}
};

#endif