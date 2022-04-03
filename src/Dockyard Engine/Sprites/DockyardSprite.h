#ifndef _DockyardSprite
#define _DockyardSprite

#include "AzulCore.h"

// forward declaration
class Camera;

class DockyardSprite
{
public:
	// big four
	DockyardSprite() = delete;
	DockyardSprite(std::string imageName);
	DockyardSprite(const DockyardSprite&) = delete;
	DockyardSprite& operator = (const DockyardSprite&) = delete;
	~DockyardSprite();

	void Render(Camera* pCam);

	// get
	float GetAngle();
	float GetWidth();
	float GetHeight();
	// set
	void SetAngle(float a);
	void SetCenter(float offsetX, float offsetY);
	void SetPosition(float x, float y);
	void SetScaleFactor(float x, float y);
	void SetScalePixel(float width, float height);

private:
	float angle;
	float centerX, centerY;
	float scaleX, scaleY;

	GraphicsObject_Sprite* gObjSprite;

	void UpdateWorld();
};

#endif