#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class Updatable;

class UpdateDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	UpdateDeregistrationCommand() = delete;
	UpdateDeregistrationCommand(Updatable* thisUpdatable);
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand&) = delete;
	UpdateDeregistrationCommand& operator = (const UpdateDeregistrationCommand&) = delete;
	virtual ~UpdateDeregistrationCommand() = default;

	void Execute() override;

private:
	Updatable* myUpdatable;
};

#endif