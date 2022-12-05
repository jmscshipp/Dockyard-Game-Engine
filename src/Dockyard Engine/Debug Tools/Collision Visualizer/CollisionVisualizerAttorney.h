#ifndef _CollisionVisualizerAttorney
#define _CollisionVisualizerAttorney

#include "CollisionVisualizer.h"

class CollisionVisualizerAttorney
{
public:
	// big four
	CollisionVisualizerAttorney() = default;
	CollisionVisualizerAttorney(const CollisionVisualizerAttorney&) = delete;
	CollisionVisualizerAttorney& operator = (const CollisionVisualizerAttorney&) = delete;
	~CollisionVisualizerAttorney() = default;

	class System
	{
		friend class Dockyard;
	private:
		static void ProcessCollisionVisuals() { CollisionVisualizer::ProcessCollisionVisuals(); }
		static void Delete() { CollisionVisualizer::Delete(); }
	};

	class Registration
	{
		friend class VisualizeCommandBSphere;
		friend class VisualizeCommandAABB;
		friend class VisualizeCommandOBB;
		friend class VisualizeCommandBoxAtPoint;
		friend class VisualizeCommandLine;

	private:
		static void RenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color) { CollisionVisualizer::RenderBSphere(sphere, color); }
		static void RenderAABB(const CollisionVolumeAABB& box, const Vect& color) { CollisionVisualizer::RenderAABB(box, color); }
		static void RenderOBB(const CollisionVolumeOBB& box, const Vect& color) { CollisionVisualizer::RenderOBB(box, color); }
		static void RenderBoxAtPoint(float x, float y, float z, const Vect& color) { CollisionVisualizer::RenderBoxAtPos(x, y, z, color); };
		static void RenderLine(const Vect& pos, const Vect& rotDir, const Vect& color) { CollisionVisualizer::RenderLine(pos, rotDir, color); };
	};
};

#endif