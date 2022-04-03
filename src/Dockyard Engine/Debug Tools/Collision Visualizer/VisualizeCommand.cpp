#include "VisualizeCommand.h"
#include "CollisionVisualizerAttorney.h"

VisualizeCommand::VisualizeCommand(const CollisionVolumeBSphere& sphere, const Vect& color)
	: colSphere(sphere),
	displayColor(color)
{
}

void VisualizeCommand::Execute()
{
	CollisionVisualizerAttorney::Registration::RenderBSphere(colSphere, displayColor);
}