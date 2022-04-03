#ifndef _SceneChangeCommand
#define _SceneChangeCommand

#include "SceneChangeCommandBase.h"

class SceneChangeCommand : public SceneChangeCommandBase
{
public:
	// big four
	SceneChangeCommand() = default;
	SceneChangeCommand(const SceneChangeCommand&) = delete;
	SceneChangeCommand& operator = (const SceneChangeCommand&) = delete;
	virtual ~SceneChangeCommand() = default;

	void SetSceneToChangeTo(Scene*) override;
	void Execute() override;

private:
};

#endif