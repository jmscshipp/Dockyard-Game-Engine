#include "VisualizeCommandBSphere.h"
#include "CollisionVisualizerAttorney.h"
#include "VisualizeCommandPool.h"

void VisualizeCommandBSphere::Initialize(const CollisionVolumeBSphere& sphere, const Vect& color)
{
	colSphere = &sphere;
	displayColor = &color;
}

void VisualizeCommandBSphere::Execute(VisualizeCommandPool* pool)
{
	CollisionVisualizerAttorney::Registration::RenderBSphere(*colSphere, *displayColor);
	pool->ReturnVisualizeCommand(this);
}