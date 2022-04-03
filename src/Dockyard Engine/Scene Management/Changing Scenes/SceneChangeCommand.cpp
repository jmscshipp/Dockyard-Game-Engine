#include "SceneChangeCommand.h"
#include "SceneManagerAttorney.h"

void SceneChangeCommand::SetSceneToChangeTo(Scene* sceneToChangeTo)
{
	nextScene = sceneToChangeTo;
}

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::Commands::ChangeScene(nextScene);
}