#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* thisDrawable)
	:myDrawable(thisDrawable)
{
}

void DrawRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneRegistration(myDrawable);
}