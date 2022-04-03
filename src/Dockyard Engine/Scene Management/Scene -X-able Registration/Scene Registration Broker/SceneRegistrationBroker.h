#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <list>

//forward declaration
class SceneRegistrationCommand;

class SceneRegistrationBroker
{
public:
	// big four
	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator = (const SceneRegistrationBroker&) = delete;
	~SceneRegistrationBroker() = default;

	void AddCommand(SceneRegistrationCommand* command);
	void ExecuteCommands();

private:
	using CommandList = std::list<SceneRegistrationCommand*>;
	CommandList lstCommands;
};

#endif