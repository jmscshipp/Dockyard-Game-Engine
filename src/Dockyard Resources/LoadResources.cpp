#include "Dockyard.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "SpriteFontManager.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "MainScene.h"

void Dockyard::LoadResources()
{
	// load models
	ModelManager::LoadModel("ModelAxis", "Axis.azul");
	ModelManager::LoadModel("ModelPlane", "Plane.azul");

	ModelManager::LoadModel("ModelSpaceFrigate", "space_frigate.azul");
	ModelManager::LoadModel("cottage", "Cottage.azul");
	ModelManager::LoadModel("ModelSphere", Model::PreMadeModels::UnitSphere);
	//ModelManager::LoadModel("ModelSphere", Model::PreMadeModels::uni);
	//ModelManager::LoadModel("character", "character.obj");

	// load textures
	TextureManager::LoadTexture("space_frigate", 150, 50, 20, 255);
	TextureManager::LoadTexture("bullet", 163, 177, 217, 255);
	TextureManager::LoadTexture("stitch", "stitch.tga");
	ImageManager::Load("stitch", TextureManager::GetTexture("stitch"));
	TextureManager::LoadTexture("minimap", "map.tga");
	ImageManager::Load("minimap", TextureManager::GetTexture("minimap"));
	TextureManager::LoadTexture("playerMapMarker", "playerMapMarker.tga");
	ImageManager::Load("playerMarker", TextureManager::GetTexture("playerMapMarker"));
	//TextureManager::LoadTexture("space_frigate", "space_frigate.tga");
	TextureManager::LoadTexture("grid", "grid.tga");

	ModelManager::LoadModel("mailmanIdle", "mailmanIdle.azul");
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

	TextureManager::LoadTexture("DockyardPalette", "DockyardPalette.tga");
	TextureManager::LoadTexture("skybox", "skyboxtex.tga");
	TextureManager::LoadTexture("StoneTexture", "StoneTexture.tga");

	TextureManager::LoadTexture("N", "N.tga");
	ImageManager::Load("N", TextureManager::GetTexture("N"));
	TextureManager::LoadTexture("E", "E.tga");
	ImageManager::Load("E", TextureManager::GetTexture("E"));
	TextureManager::LoadTexture("S", "S.tga");
	ImageManager::Load("S", TextureManager::GetTexture("S"));
	TextureManager::LoadTexture("W", "W.tga");
	ImageManager::Load("W", TextureManager::GetTexture("W"));

	TextureManager::LoadTexture("letter", "letter.tga");
	ImageManager::Load("letter", TextureManager::GetTexture("letter"));

	TextureManager::LoadTexture("compass", "compass.tga");
	ImageManager::Load("compass", TextureManager::GetTexture("compass"));

	// load shaders
	ShaderManager::LoadShader("texture", "textureFlatRender");
	ShaderManager::LoadShader("textureLight", "textureLightRender");
	//ShaderObject *pShaderObject_varyColor = new ShaderObject("colorVaryRender");
	ShaderManager::LoadShader("constantColor", "colorConstantRender");
	ShaderManager::LoadShader("colorNoTexture", "colorNoTextureRender");
	//ShaderObject *pShaderObject_colorNoTextureLight = new ShaderObject("colorNoTextureLightRender");
	//ShaderObject *pShaderObject_colorByPosition = new ShaderObject("colorVaryRender");
	//ShaderObject *pShaderObject_sprite = new ShaderObject("spriteRender");
	//ShaderObject *pShaderObject_spriteLine = new ShaderObject("spriteLineRender");

	SpriteFontManager::LoadSpriteFont("DreamOrphansFont", "DreamOrphans");
	SpriteFontManager::LoadSpriteFont("AdobeFont", "adobefont");

	//SceneManager::SetNextScene(new DemoScene());
	SceneManager::SetNextScene(new MainScene());
}