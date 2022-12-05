#include "CollisionVolumeOBB.h"
#include "CollisionVisualizer.h"
#include "DockyardMathTools.h"
#include "GraphicsCore.h"

void CollisionVolumeOBB::ComputeData(Model* mod, const Matrix& mat)
{
	min = mod->GetMinAABB();
	max = mod->GetMaxAABB();
	world = mat;
	halfDiagonal = 0.5f * (max - min);
	center = (min + halfDiagonal) * world;
	scaleSqrd = (Vect(0, 0, 1, 0) * world).magSqr();
}

void CollisionVolumeOBB::DebugView(const Vect& color) const
{
	CollisionVisualizer::ShowOBB(*this, color);
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return MathFunctions::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return MathFunctions::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return MathFunctions::Intersect(*this, other);
}

// access private members
const Vect& CollisionVolumeOBB::GetMin() const
{
	return min;
}

const Vect& CollisionVolumeOBB::GetMax() const
{
	return max;
}

const Matrix& CollisionVolumeOBB::GetWorld() const
{
	return world;
}

const Vect& CollisionVolumeOBB::GetHalfDiagonal() const
{
	return halfDiagonal;
}

const float CollisionVolumeOBB::GetScaleSqrd() const
{
	return scaleSqrd;
}

const Vect& CollisionVolumeOBB::GetCenter() const
{
	return center;
}