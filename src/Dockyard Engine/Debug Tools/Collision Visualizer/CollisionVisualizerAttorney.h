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
		friend class VisualizeCommand;
	private:
		static void RenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color) { CollisionVisualizer::RenderBSphere(sphere, color); }
	};
};

#endif