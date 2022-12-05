#include "VisualizeCommandOBB.h"
#include "CollisionVisualizerAttorney.h"
#include "VisualizeCommandPool.h"

void VisualizeCommandOBB::Initialize(const CollisionVolumeOBB& box, const Vect& color)
{
	colVolume = &box;
	displayColor = &color;
}

void VisualizeCommandOBB::Execute(VisualizeCommandPool* pool)
{
	CollisionVisualizerAttorney::Registration::RenderOBB(*colVolume, *displayColor);
	pool->ReturnVisualizeCommand(this);
}