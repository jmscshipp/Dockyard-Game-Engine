#include "Dockyard.h"

void Dockyard::GameInitialize()
{
	// Game Window Device setup
	this->setWindowName("Dockyard Engine");
	this->setWidthHeight(800, 600);
	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);

	// Use this area, for one time non-graphic creation
}