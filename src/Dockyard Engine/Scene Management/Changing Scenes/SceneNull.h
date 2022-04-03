#ifndef _SceneNull
#define _SceneNull

#include "Scene.h"

class SceneNull : public Scene
{
public:
	// big four
	SceneNull() = default;
	SceneNull(const SceneNull&) = delete;
	SceneNull& operator = (const SceneNull&) = delete;
	~SceneNull() = default;

	void Initialize() override {};
	void SceneEnd() override {};

private:

};

#endif