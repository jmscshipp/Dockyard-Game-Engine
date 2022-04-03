#ifndef _SceneRegistrationCommand
#define _SceneRegistrationCommand

class SceneRegistrationCommand
{
public:
	// big four
	SceneRegistrationCommand() = default;
	SceneRegistrationCommand(const SceneRegistrationCommand&) = delete;
	SceneRegistrationCommand& operator = (const SceneRegistrationCommand&) = delete;
	virtual ~SceneRegistrationCommand() = default;

	virtual void Execute() = 0;

private:

};

#endif