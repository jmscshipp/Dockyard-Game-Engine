#ifndef _Drawable
#define _Drawable

#include "SceneRegistrationState.h"
#include "DrawableManager.h"

// forward declarations
class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{
public:
	// big four
	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator = (const Drawable&) = delete;
	virtual ~Drawable();

protected:
	void SubmitDrawRegistration();
	void SubmitDrawDeregistration();

private:
	virtual void Draw() {};
	virtual void Draw2D() {};
	void SceneRegistration();
	void SceneDeregistration();

	DrawRegistrationCommand* registerCmd;
	DrawDeregistrationCommand* deregisterCmd;
	SceneRegistrationState currentState;
	DrawableManager::StorageListRef myDeletePtr;

	friend class DrawableAttorney; // this is so commands can access scene (de)registration()
};

#endif