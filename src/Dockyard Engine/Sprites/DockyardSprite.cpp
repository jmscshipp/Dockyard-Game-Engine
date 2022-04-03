#include "DockyardSprite.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"

DockyardSprite::DockyardSprite(std::string imageName)
	:angle(0.0f),
	centerX(0.0f),
	centerY(0.0f),
	scaleX(1.0f),
	scaleY(1.0f)
{
	Image* myImage = ImageManager::GetImage(imageName);
	gObjSprite = new GraphicsObject_Sprite(ModelManager::GetModel("defaultSpriteModel"), ShaderManager::GetShader("defaultSpriteShader"), myImage, myImage->pImageRect);
}

DockyardSprite::~DockyardSprite()
{
	delete gObjSprite;
}

void DockyardSprite::Render(Camera* pCam)
{
	gObjSprite->Render(pCam);
}

float DockyardSprite::GetAngle()
{
	return angle;
}

float DockyardSprite::GetWidth()
{
	return gObjSprite->origWidth * scaleX;
}

float DockyardSprite::GetHeight()
{
	return gObjSprite->origHeight * scaleY;
}

void DockyardSprite::SetAngle(float a)
{
	angle = a;
	UpdateWorld();
}

void DockyardSprite::SetCenter(float offsetX, float offsetY)
{
	centerX = offsetX;
	centerY = offsetY;
	UpdateWorld();
}

void DockyardSprite::SetPosition(float x, float y)
{
	gObjSprite->origPosX = x;
	gObjSprite->origPosY = y;
	UpdateWorld();
}

void DockyardSprite::SetScaleFactor(float x, float y)
{
	scaleX = x;
	scaleY = y;
	UpdateWorld();
}

void DockyardSprite::SetScalePixel(float width, float height)
{
	scaleX = width / gObjSprite->origWidth;
	scaleY = height / gObjSprite->origHeight;
	UpdateWorld();
}

void DockyardSprite::UpdateWorld()
{
	Matrix scale = Matrix(SCALE, scaleX, scaleY, 1.0f);
	Matrix rot = Matrix(TRANS, -centerX, -centerY, 0.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, centerX, centerY, 0.0f);
	Matrix trans = Matrix(TRANS, gObjSprite->origPosX, gObjSprite->origPosY, 0.0f);
	Matrix world = scale * rot * trans;
	gObjSprite->SetWorld(world);
}