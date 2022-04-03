#include "CameraManager.h"
#include "Dockyard.h"

CameraManager::CameraManager()
{
	// set up default orthographic camera
	orthoCam = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	orthoCam->setViewport(0, 0, Dockyard::GetWidth(), Dockyard::GetHeight());
	orthoCam->setOrthographic(-0.5f * Dockyard::GetWidth(), 0.5f * Dockyard::GetWidth(), -0.5f * Dockyard::GetHeight(), 0.5f * Dockyard::GetHeight(), 1.0f, 1000.0f);
	orthoCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, -1.0f), Vect(0.0f, 0.0f, 0.0f)); // upcam, lookat2dcam, pos2dcam
	orthoCam->updateCamera();
	// set up default 3d camera
	defaultCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	defaultCam->setViewport(0, 0, Dockyard::GetWidth(), Dockyard::GetHeight());
	defaultCam->setPerspective(35.0f, float(Dockyard::GetWidth()) / float(Dockyard::GetHeight()), 1.0f, 5000.0f);
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