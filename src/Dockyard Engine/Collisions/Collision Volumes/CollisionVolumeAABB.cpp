#include "CollisionVolumeAABB.h"
#include "CollisionVisualizer.h"
#include "DockyardMathTools.h"
#include "GraphicsCore.h"

void CollisionVolumeAABB::ComputeData(Model* mod, const Matrix& mat)
{
	// iterate through verts to determine min and max
	StandardVertex* verts = mod->GetVertexArray();
	Vect temp = verts[0].Pos * mat;
	min = max = temp;

	// set min and max
	for (int i = 0; i < mod->GetVertexNum(); i++)
	{
		temp = verts[i].Pos * mat;
		if (temp.X() < min.X())
			min.X() = temp.X();
		else if (temp.X() > max.X())
			max.X() = temp.X();

		if (temp.Y() < min.Y())
			min.Y() = temp.Y();
		else if (temp.Y() > max.Y())
			max.Y() = temp.Y();

		if (temp.Z() < min.Z())
			min.Z() = temp.Z();
		else if (temp.Z() > max.Z())
			max.Z() = temp.Z();
	}

	// extra OBB stuff for OBB collisions
	world = Matrix(IDENTITY);
	halfDiagonal = (0.5f * (max - min)) * world.getInv();
	center = min + (0.5f * (max - min));
	scaleSqrd = (Vect(0, 0, 1, 0) * world).magSqr();
}

void CollisionVolumeAABB::ComputeData(const Vect& _min, const Vect& _max)
{
	// assign directly
	min = _min;
	max = _max;
	// extra OBB stuff for OBB collisions
	world = Matrix(IDENTITY);
	halfDiagonal = (0.5f * (max - min)) * world.getInv();
	center = min + (0.5f * (max - min));
	scaleSqrd = (Vect(0, 0, 1, 0) * world).magSqr();
}

void CollisionVolumeAABB::DebugView(const Vect& color) const
{
	CollisionVisualizer::ShowAABB(*this, color);
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return MathFunctions::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return MathFunctions::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return MathFunctions::Intersect(*this, other);
}

// access private members
const Vect& CollisionVolumeAABB::GetMin() const
{
	return min;
}

const Vect& CollisionVolumeAABB::GetMax() const
{
	return max;
}

const Matrix& CollisionVolumeAABB::GetWorld() const
{
	return world;
}

const Vect& CollisionVolumeAABB::GetHalfDiagonal() const
{
	return halfDiagonal;
}

const float CollisionVolumeAABB::GetScaleSqrd() const
{
	return scaleSqrd;
}

const Vect& CollisionVolumeAABB::GetCenter() const
{
	return center;
}