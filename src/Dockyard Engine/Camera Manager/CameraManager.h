#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"

class CameraManager
{
public:
	// big four
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator = (const CameraManager&) = delete;
	~CameraManager();

	void SetCurrentCamera(Camera* cam);
	Camera* GetCurrentCamera();
	Camera* GetDefaultOrthoCam();

private:
	Camera* currentCam;
	Camera* defaultCam;
	Camera* orthoCam;
};

#endif