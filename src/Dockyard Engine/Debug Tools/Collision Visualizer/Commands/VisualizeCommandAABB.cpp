#include "VisualizeCommandAABB.h"
#include "CollisionVisualizerAttorney.h"
#include "VisualizeCommandPool.h"

void VisualizeCommandAABB::Initialize(const CollisionVolumeAABB& box, const Vect& color)
{
	colVolume = &box;
	displayColor = &color;
}

void VisualizeCommandAABB::Execute(VisualizeCommandPool* pool)
{
	CollisionVisualizerAttorney::Registration::RenderAABB(*colVolume, *displayColor);
	pool->ReturnVisualizeCommand(this);
}