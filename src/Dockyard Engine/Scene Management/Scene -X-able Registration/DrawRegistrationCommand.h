#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class Drawable;

class DrawRegistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(Drawable* thisUpdatable);
	DrawRegistrationCommand(const DrawRegistrationCommand&) = delete;
	DrawRegistrationCommand& operator = (const DrawRegistrationCommand&) = delete;
	virtual ~DrawRegistrationCommand() = default;

	void Execute() override;

private:
	Drawable* myDrawable;
};

#endif