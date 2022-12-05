#include "VisualizeCommandLine.h"
#include "CollisionVisualizerAttorney.h"
#include "VisualizeCommandPool.h"

void VisualizeCommandLine::Initialize(const Vect& _pos, const Vect& _rotDir, const Vect& _color)
{
	pos = _pos;
	rotDir = _rotDir;
	color = _color;
}

void VisualizeCommandLine::Execute(VisualizeCommandPool* pool)
{
	CollisionVisualizerAttorney::Registration::RenderLine(pos, rotDir, color);
	pool->ReturnVisualizeCommand(this);
}