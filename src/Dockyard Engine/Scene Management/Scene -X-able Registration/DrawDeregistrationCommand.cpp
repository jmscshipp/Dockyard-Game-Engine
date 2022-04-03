#include "DrawDeregistrationCommand.h"
#include "DrawableAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* thisDrawable)
	:myDrawable(thisDrawable)
{
}

void DrawDeregistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneDeregistration(myDrawable);
}