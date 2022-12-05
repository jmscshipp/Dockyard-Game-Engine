#include "Dockyard.h"
#include "WindowController.h"
#include "ColorLibrary.h"

void Dockyard::GameInitialize()
{
	WindowController::SetWindowName("Dockyard Engine");
	WindowController::SetWindowWidthHeight(800, 600);
	Dockyard::SetBackgroundColor(Colors::SkyBlue);
}