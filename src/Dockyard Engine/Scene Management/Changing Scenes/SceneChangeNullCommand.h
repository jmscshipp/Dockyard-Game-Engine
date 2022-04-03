#ifndef _SceneChangeNullCommand
#define _SceneChangeNullCommand

#include "SceneChangeCommandBase.h"

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	// big four
	SceneChangeNullCommand() = default;
	SceneChangeNullCommand(const SceneChangeNullCommand&) = delete;
	SceneChangeNullCommand& operator = (const SceneChangeNullCommand&) = delete;
	virtual ~SceneChangeNullCommand() = default;

	virtual void SetSceneToChangeTo(Scene*) override {};
	void Execute() override {};

private:
};

#endif