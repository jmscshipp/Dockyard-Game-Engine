#include "Dockyard.h"
#include "AzulCore.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "ImageManagerAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "SceneManagerAttorney.h"
#include "CollisionVisualizerAttorney.h"
#include "ScreenLogAttorney.h"

Dockyard* Dockyard::instance = nullptr;
//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Dockyard::Initialize()
{
	GameInitialize();
}

// loads engine content
void Dockyard::LoadContent()
{
	this->LoadResources();
}

float Dockyard::PrivGetTimeInSeconds()
{
	return Engine::GetTimeInSeconds();
}

void Dockyard::PrivRun()
{
	this->run();
	Delete();
}

int Dockyard::PrivGetWidth()
{
	return Engine::getWidth();
}

int Dockyard::PrivGetHeight()
{
	return Engine::getHeight();
}

void Dockyard::PrivSetWindowName(const char* name)
{
	this->setWindowName(name);
}

void Dockyard::PrivSetWidthHeight(int w, int h)
{
	this->setWidthHeight(w, h);
}

void Dockyard::PrivSetClear(float r, float g, float b, float a)
{
	this->SetClearColor(r, g, b, a);
}

void Dockyard::Delete()
{
	delete instance;
	instance = nullptr;
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Dockyard::Update()
{
	TimeManagerAttorney::System::ProcessTime();
	SceneManagerAttorney::General::Update();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Dockyard::Draw()
{
	CollisionVisualizerAttorney::System::ProcessCollisionVisuals();
	SceneManagerAttorney::General::Draw();
	ScreenLogAttorney::Render();
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Dockyard::UnLoadContent()
{
	// asset clean up
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();

	// debug systems clean up
	CollisionVisualizerAttorney::System::Delete();
	ScreenLogAttorney::Delete();

	// other systems clean up
	SceneManagerAttorney::General::Delete();
	TimeManagerAttorney::System::Delete();

	GameEnd();
}


