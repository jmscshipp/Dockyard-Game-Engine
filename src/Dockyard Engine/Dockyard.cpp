#include "Dockyard.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "TerrainManagerAttorney.h"
#include "ImageManagerAttorney.h"
//#include "SpriteFontManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "TimeManager.h"
#include "SceneManagerAttorney.h"
#include "CollisionVisualizerAttorney.h"
#include "ScreenLogAttorney.h"
#include "WindowController.h"
#include "GPUController.h"

Dockyard* Dockyard::instance = nullptr;
//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Dockyard::NonstaticInitialize(HWND hwnd)
{
	assert(hwnd);

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(hwnd, &rc);
	assert(err);

	// get width/hight
	int mClientWidth = rc.right - rc.left;
	int mClientHeight = rc.bottom - rc.top;

	// init dx 11
	GPUController::InitDirect3D(hwnd, mClientWidth, mClientHeight);

	GameInitialize();
	SceneManagerAttorney::General::Instance();
	LoadResources();
}

int Dockyard::PrivGetWidth()
{
	return WindowController::GetWindowWidth();
}

int Dockyard::PrivGetHeight()
{
	return WindowController::GetWindowHeight();
}

void Dockyard::PrivSetWindowName(const char* name)
{
	WindowController::SetWindowName(name);
}

void Dockyard::PrivSetWidthHeight(int w, int h)
{
	WindowController::SetWindowWidthHeight(w, h);
}

void Dockyard::PrivSetBackgroundColor(const Vect& color)
{
	GPUController::SetBackgroundColor(color);
}

void Dockyard::NonstaticDelete()
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
void Dockyard::NonstaticUpdate()
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
void Dockyard::NonstaticDraw()
{
	GPUController::ResetContext();
	CollisionVisualizerAttorney::System::ProcessCollisionVisuals();
	SceneManagerAttorney::General::Draw();
	//ScreenLogAttorney::Render();
	GPUController::SwapChainSwitch();
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
Dockyard::~Dockyard()
{
	// asset clean up
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	TerrainManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	//SpriteFontManagerAttorney::Delete();

	// debug systems clean up
	CollisionVisualizerAttorney::System::Delete();
	//ScreenLogAttorney::Delete();

	// other systems clean up
	SceneManagerAttorney::General::Delete();
	TimeManagerAttorney::System::Delete();
	
	// directx stuff clean up
	GPUController::Delete();

	Instance().GameEnd();
}