#ifndef _DockyardMathTools
#define _DockyardMathTools

#include "CollisionVolume.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolumeBBBase.h"
#include "CollisionVisualizer.h"

// James Shipp 2022
// Code sample from my 3D math functions class
class MathFunctions
{
public:
	// General intersection function to reroute to col volumes for visitor pattern
	static bool Intersect(const CollisionVolume& A, const CollisionVolume& B)
	{
		return A.IntersectAccept(B);
	}

	// Bsphere - Bsphere intersection test
	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
	{
		float centerDistance = (A.GetCenter() - B.GetCenter()).mag();
		float radiusSum = A.GetRadius() + B.GetRadius();
		if (radiusSum > centerDistance)
			return true;
		return false;
	}

	// AABB - AABB intersection test
	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B)
	{
		Vect maxA = A.GetMax();
		Vect maxB = B.GetMax();
		Vect minA = A.GetMin();
		Vect minB = B.GetMin();

		if (IntervalOverlapTest(minA.X(), maxA.X(), minB.X(), maxB.X()) && IntervalOverlapTest(minA.Y(), maxA.Y(), minB.Y(), maxB.Y())
			&& IntervalOverlapTest(minA.Z(), maxA.Z(), minB.Z(), maxB.Z()))
			return true;
		return false;
	}

	// OBB - OBB / AABB intersection test
	static bool Intersect(const CollisionVolumeBBBase& A, const CollisionVolumeBBBase& B)
	{
		// get face normals for xyz on A and B, and cross products between them
		Vect axes[15] = {};
		axes[0] = A.GetWorld().get(ROW_0); // A x axis
		axes[1] = A.GetWorld().get(ROW_1); // A y axis
		axes[2] = A.GetWorld().get(ROW_2); // A z axis
		axes[3] = B.GetWorld().get(ROW_0); // B x axis
		axes[4] = B.GetWorld().get(ROW_1); // B y axis
		axes[5] = B.GetWorld().get(ROW_2); // B z axis
		axes[6] = axes[0].cross(axes[3]); // A x cross B x
		axes[7] = axes[0].cross(axes[4]); // A x cross B y
		axes[8] = axes[0].cross(axes[5]); // A x cross B z
		axes[9] = axes[1].cross(axes[3]); // A y cross B x
		axes[10] = axes[1].cross(axes[4]); // A y cross B y
		axes[11] = axes[1].cross(axes[5]); // A y cross B z
		axes[12] = axes[2].cross(axes[3]); // A z cross B x
		axes[13] = axes[2].cross(axes[4]); // A z cross B y
		axes[14] = axes[2].cross(axes[5]); // A z cross B z

		// correct W component of crosses, which defaults to 1
		axes[6].W() = 0.0f;
		axes[7].W() = 0.0f;
		axes[8].W() = 0.0f;
		axes[9].W() = 0.0f;
		axes[10].W() = 0.0f;
		axes[11].W() = 0.0f;
		axes[12].W() = 0.0f;
		axes[13].W() = 0.0f;
		axes[14].W() = 0.0f;

		for (int i = 0; i < 15; i++)
		{
			// makes sure we don't divide by 0 further down the line
			if (!VectIsZero(axes[i]))
			{
				float centerDist = VectProjectionLength(B.GetCenter() - A.GetCenter(), axes[i]);
				float diagProjDistance = MaxBBProjectionOnAxis(A, axes[i]) + MaxBBProjectionOnAxis(B, axes[i]);
				// if projection between OBB centers on the axis is bigger than combined half diag projections, no collision
				if ( centerDist >=  diagProjDistance)
					return false;
			}
		}
		// if no axes flag false, collision!
		return true;
	}

	// BSphere - AABB intersection test
	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B)
	{
		// get bsphere center clamped to AABB
		Vect clampedSphereCenter = Vect(ClampValInInterval(A.GetCenter().X(), B.GetMin().X(), B.GetMax().X()),
			ClampValInInterval(A.GetCenter().Y(), B.GetMin().Y(), B.GetMax().Y()),
			ClampValInInterval(A.GetCenter().Z(), B.GetMin().Z(), B.GetMax().Z()));

		//CollisionVisualizer::ShowBoxAtPos(clampedSphereCenter.X(), clampedSphereCenter.Y(), clampedSphereCenter.Z());

		// compare distance of centers to bsphere radius
		float centerDistance = (A.GetCenter() - clampedSphereCenter).mag();
		if (A.GetRadius() > centerDistance)
			return true;
		return false;
	}

	// BSphere - OBB intersection test
	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B)
	{
		// move bsphere center to obb localspace
		Vect sphereCenterLocal = A.GetCenter() * B.GetWorld().getInv();

		// get clamped value of center 
		Vect clampedSphereCenter = Vect(ClampValInInterval(sphereCenterLocal.X(), B.GetMin().X(), B.GetMax().X()),
			ClampValInInterval(sphereCenterLocal.Y(), B.GetMin().Y(), B.GetMax().Y()),
			ClampValInInterval(sphereCenterLocal.Z(), B.GetMin().Z(), B.GetMax().Z()));

		// moved clamped center back to world space
		clampedSphereCenter *= B.GetWorld();

		// compare distance of centers to bsphere radius
		float centerDistance = (A.GetCenter() - clampedSphereCenter).mag();
		if (A.GetRadius() > centerDistance)
			return true;
		return false;
	}

	// AABB - point intersection test
	static bool PointInAABB(const Vect& maxAABB, const Vect& minAABB, const Vect& point)
	{
		if ((point.X() < maxAABB.X() && point.X() > minAABB.X()) && (point.Y() < maxAABB.Y() && point.Y() > minAABB.Y())
			&& (point.Z() < maxAABB.Z() && point.Z() > minAABB.Z()))
			return true;
		return false;
	}

	// OBB - point intersection test
	static bool PointInOBB(const CollisionVolumeOBB& A, const Vect& point)
	{
		Vect localPoint = point * A.GetWorld().getInv();
		return PointInAABB(A.GetMax(), A.GetMin(), localPoint);
	}

	// Interval - interval intersection test
	static bool IntervalOverlapTest(float firstIntervalMin, float firstIntervalMax, float secondIntervalMin, float secondIntervalMax)
	{
		if (firstIntervalMax < secondIntervalMin || secondIntervalMax < firstIntervalMin)
			return false;
		return true;
	}

	// clamps
	static float ClampValInInterval(float val, float intervalMin, float intervalMax)
	{
		if (val < intervalMin)
			return intervalMin;
		if (val > intervalMax)
			return intervalMax;
		return val;
	}

	// prevent near-zero vects from math errors
	static bool VectIsZero(const Vect& v)
	{
		if (v.magSqr() > 0.05f)
			return false;
		return true;
	}

	// length of projecting projectedVect onto controlVect
	static float VectProjectionLength(const Vect& projectedVect, const Vect& controlVect)
	{
		return projectedVect.dot(controlVect) / controlVect.mag();
	}

	// returns resulting vect of projecting projectedVect onto controlVect
	static Vect VectProjectionUnitVect(const Vect& projectedVect, const Vect& controlVect)
	{
		return (projectedVect.dot(controlVect) / controlVect.dot(controlVect)) * controlVect;
	}

	// applies for both AABB and OBB for OBB collisions
	static float MaxBBProjectionOnAxis(const CollisionVolumeBBBase& vol, const Vect& projAxis)
	{
		Vect localProjAxis = projAxis * vol.GetWorld().getInv();
		float maxProj = (abs(localProjAxis.X() * vol.GetHalfDiagonal().X()) + abs(localProjAxis.Y() * vol.GetHalfDiagonal().Y())
			+ abs(localProjAxis.Z() * vol.GetHalfDiagonal().Z())) / projAxis.mag();
		return vol.GetScaleSqrd() * maxProj;
	}
};

#endif