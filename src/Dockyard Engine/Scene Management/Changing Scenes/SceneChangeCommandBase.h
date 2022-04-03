#ifndef _SceneChangeCommandBase
#define _SceneChangeCommandBase

// forward declaration
class Scene;

class SceneChangeCommandBase
{
public:
	// big four
	SceneChangeCommandBase() = default;
	SceneChangeCommandBase(const SceneChangeCommandBase&) = delete;
	SceneChangeCommandBase& operator = (const SceneChangeCommandBase&) = delete;
	virtual ~SceneChangeCommandBase() = default;

	virtual void SetSceneToChangeTo(Scene*) = 0;
	virtual void Execute() = 0;

protected:
	Scene* nextScene;
};

#endif