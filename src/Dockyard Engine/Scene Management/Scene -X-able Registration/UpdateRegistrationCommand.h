#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class Updatable;

class UpdateRegistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(Updatable* thisUpdatable);
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = delete;
	UpdateRegistrationCommand& operator = (const UpdateRegistrationCommand&) = delete;
	virtual ~UpdateRegistrationCommand() = default;

	void Execute() override;

private:
	Updatable* myUpdatable;
};

#endif