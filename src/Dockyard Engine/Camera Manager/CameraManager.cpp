#include "CameraManager.h"
#include "Dockyard.h"
#include "Vect.h"

CameraManager::CameraManager()
{
	// set up default orthographic camera
	orthoCam = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	orthoCam->SetOrthographic(-0.5f * Dockyard::GetWidth(), 0.5f * Dockyard::GetWidth(), -0.5f * Dockyard::GetHeight(), 0.5f * Dockyard::GetHeight(), 1.0f, 1500.0f);
	orthoCam->SetOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, -10.0f)); // upcam, lookat2dcam, pos2dcam)
	orthoCam->UpdateCamera();

	// set up default 3d camera
	defaultCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	defaultCam->SetPerspective(3.14159 / 3, float(Dockyard::GetWidth()) / float(Dockyard::GetHeight()), 1.0f, 5000.0f);
	defaultCam->UpdateCamera();
	currentCam = defaultCam;
}

CameraManager::~CameraManager()
{
	delete defaultCam;
	delete orthoCam;
}

void CameraManager::SetCurrentCamera(Camera* cam)
{
	currentCam = cam;
}

Camera* CameraManager::GetCurrentCamera()
{
	return currentCam;
}

Camera* CameraManager::GetDefaultOrthoCam()
{
	return orthoCam;
}