#include "CollisionVolumeBSphere.h"
#include "CollisionVisualizer.h"
#include "DockyardMathTools.h"
#include "ColorLibrary.h"
#include "CollisionVolumeAABB.h"
#include "GraphicsCore.h"

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	// change center
	center = mod->GetCenter() * mat;
	// get magnitude of first row, multiply by model radius
	radius = mod->GetRadius() * mat.get(MatrixRowType::ROW_0).mag();
	// get min and max in world
	min = center + Vect(-radius, -radius, -radius);
	max = center + Vect(radius, radius, radius);
}

void CollisionVolumeBSphere::DebugView(const Vect& color) const
{
	CollisionVisualizer::ShowBSphere(*this, color);
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return MathFunctions::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return MathFunctions::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return MathFunctions::Intersect(*this, other);
}

// access private members
const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return radius;
}

const Vect& CollisionVolumeBSphere::GetMin() const
{
	return min;
}

const Vect& CollisionVolumeBSphere::GetMax() const
{
	return max;
}