#include "CollisionVolumeBSphere.h"

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	// change center
	center = mod->getCenter() * mat;
	// get magnitude of first row, multiply by model radius
	radius = mod->getRadius() * mat.get(MatrixRowType::ROW_0).mag();
}

//bool CollisionVolumeBSphere::Intersect(const CollisionVolume& other)
//{
//	// use math tools here later
//}

//bool CollisionVolumeBSphere::Intersect(const CollisionVolumeBSphere& other)
//{
//	// use math tools here later
//}

// access private members
const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return radius;
}