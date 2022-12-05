#include "VisualizeCommandBoxAtPoint.h"
#include "CollisionVisualizerAttorney.h"
#include "VisualizeCommandPool.h"

void VisualizeCommandBoxAtPoint::Initialize(float _x, float _y, float _z, const Vect& _color)
{
	x = _x;
	y = _y;
	z = _z;
	color = &_color;
}

void VisualizeCommandBoxAtPoint::Execute(VisualizeCommandPool* pool)
{
	CollisionVisualizerAttorney::Registration::RenderBoxAtPoint(x, y, z, *color);
	pool->ReturnVisualizeCommand(this);
}