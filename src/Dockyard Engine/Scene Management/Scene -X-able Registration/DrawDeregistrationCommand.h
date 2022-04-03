#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class Drawable;

class DrawDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	DrawDeregistrationCommand() = delete;
	DrawDeregistrationCommand(Drawable* thisDrawable);
	DrawDeregistrationCommand(const DrawDeregistrationCommand&) = delete;
	DrawDeregistrationCommand& operator = (const DrawDeregistrationCommand&) = delete;
	virtual ~DrawDeregistrationCommand() = default;

	void Execute() override;

private:
	Drawable* myDrawable;
};

#endif