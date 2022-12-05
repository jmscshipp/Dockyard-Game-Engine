#include "Dockyard.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "TerrainManager.h"
//#include "SpriteFontManager.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "MainScene.h"
#include "ShaderExperimentScene.h"

void Dockyard::LoadResources()
{	
	// LOAD MODELS
	ModelManager::LoadModel("ModelAxis", "Axis.azul");
	ModelManager::LoadModel("ModelPlane", "Plane.azul");
	ModelManager::LoadModel("ModelSpaceFrigate", "space_frigate.azul");
	ModelManager::LoadModel("cottage", "Cottage.azul");
	ModelManager::LoadModel("mailmanIdle", "mailmanIdle.azul");
	ModelManager::LoadModel("mailmanOnScooter", "mailmanOnScooter.azul");
	ModelManager::LoadModel("mailmanWalk0", "mailmanWalk0.azul");
	ModelManager::LoadModel("mailmanWalk1", "mailmanWalk1.azul");
	ModelManager::LoadModel("mailmanWalk2", "mailmanWalk2.azul");
	ModelManager::LoadModel("mailmanWalk3", "mailmanWalk3.azul");
	ModelManager::LoadModel("oldman", "oldman.azul");
	ModelManager::LoadModel("oldlady0", "oldlady0.azul");
	ModelManager::LoadModel("oldlady1", "oldlady1.azul");
	ModelManager::LoadModel("oldlady2", "oldlady2.azul");
	ModelManager::LoadModel("redhouse", "redhouse.azul");
	ModelManager::LoadModel("bluehouse", "bluehouse.azul");
	ModelManager::LoadModel("greenhouse", "greenhouse.azul");
	ModelManager::LoadModel("tree", "tree.azul");
	//ModelManager::LoadModel("ModelSphere", Model::PreMadeModels::uni);
	//ModelManager::LoadModel("character", "character.obj");

	// LOAD TEXTURES
	//TextureManager::LoadTexture("space_frigate", 150, 50, 20, 255);
	//TextureManager::LoadTexture("bullet", 163, 177, 217, 255);
	TextureManager::LoadTexture("stitch", L"stitch.tga");
	TextureManager::LoadTexture("minimap", L"map.tga");
	TextureManager::LoadTexture("playerMapMarker", L"playerMapMarker.tga");
	TextureManager::LoadTexture("grid", L"grid.tga");
	TextureManager::LoadTexture("DockyardPalette", L"DockyardPalette.tga");
	TextureManager::LoadTexture("skybox", L"skyboxtex.tga");
	TextureManager::LoadTexture("StoneTexture", L"StoneTexture.tga");
	TextureManager::LoadTexture("N", L"N.tga");
	TextureManager::LoadTexture("E", L"E.tga");
	TextureManager::LoadTexture("S", L"S.tga");
	TextureManager::LoadTexture("W", L"W.tga");
	TextureManager::LoadTexture("letter", L"letter.tga");
	TextureManager::LoadTexture("compass", L"compass.tga");
	TextureManager::LoadTexture("water", L"water.tga");
	//TextureManager::LoadTexture("space_frigate", "space_frigate.tga");

	// LOAD IMAGES
	ImageManager::Load("stitch", TextureManager::GetTexture("stitch"));
	ImageManager::Load("minimap", TextureManager::GetTexture("minimap"));
	ImageManager::Load("playerMarker", TextureManager::GetTexture("playerMapMarker"));
	ImageManager::Load("N", TextureManager::GetTexture("N"));
	ImageManager::Load("E", TextureManager::GetTexture("E"));
	ImageManager::Load("S", TextureManager::GetTexture("S"));
	ImageManager::Load("W", TextureManager::GetTexture("W"));
	ImageManager::Load("letter", TextureManager::GetTexture("letter"));
	ImageManager::Load("compass", TextureManager::GetTexture("compass"));

	// LOAD SHADERS
	ShaderManager::LoadShader("textureFlat", new ShaderTexture());
	ShaderManager::LoadShader("textureLight", new ShaderTextureLight());
	ShaderManager::LoadShader("textureOutline", new ShaderOutline());
	ShaderManager::LoadShader("colorFlat", new ShaderColor());
	ShaderManager::LoadShader("colorLight", new ShaderColorLight());
	ShaderManager::LoadShader("cartoon", new ShaderCartoon());
	ShaderManager::LoadShader("water", new ShaderWater());

	// LOAD TERRAINS
	TerrainManager::LoadTerrain("MainTerrain", L"../Assets/Textures/mainSceneHM.tga", "StoneTexture", 128, 35.0f, 1000.0f, -620, 10, 10);
	TerrainManager::LoadTerrain("TestTerrain", L"../Assets/Textures/mainSceneHM.tga", "StoneTexture", 10, 35.0f, 200.0f, -120, 10, 10);

	// LOAD SPRITEFONTS
	//SpriteFontManager::LoadSpriteFont("DreamOrphansFont", "DreamOrphans");
	//SpriteFontManager::LoadSpriteFont("AdobeFont", "adobefont");
	//SpriteFontManager::LoadSpriteFont("Stencil60Font", "Stencil60");

	// LOAD SCENES
	SceneManager::SetNextScene(new ShaderExperimentScene());
	//SceneManager::SetNextScene(new DemoScene());
	//SceneManager::SetNextScene(new MainScene());
}