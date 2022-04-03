#include "CollisionVisualizer.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "CollisionVolumeBSphere.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ColorLibrary.h"
#include "SceneManager.h"
#include "Scene.h"
#include "VisualizeCommand.h"

CollisionVisualizer* CollisionVisualizer::instance = nullptr;
Vect CollisionVisualizer::DEFAULT_COLOR = Colors::Black;

CollisionVisualizer::CollisionVisualizer()
{
	wireframeUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("ModelSphere"), ShaderManager::GetShader("constantColor"), DEFAULT_COLOR);
	showSphereRequests = {};
}

CollisionVisualizer::~CollisionVisualizer()
{
	delete wireframeUnitSphere;
	for (std::list<VisualizeCommand*>::iterator it = showSphereRequests.begin(); it != showSphereRequests.end(); it++)
		delete* it;
}

void CollisionVisualizer::NonstaticRenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color)
{
	float matScale = sphere.GetRadius();
	Vect cent = sphere.GetCenter();
	// Adjust the Bounding Sphere's position and scale to fit the object's center and scale
	Matrix worldBS = Matrix(SCALE, matScale, matScale, matScale) * Matrix(TRANS, cent);

	wireframeUnitSphere->SetWorld(worldBS);
	wireframeUnitSphere->SetColor(color);
	wireframeUnitSphere->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void CollisionVisualizer::PrivShowBSphere(const CollisionVolumeBSphere& sphere, const Vect& color)
{
	showSphereRequests.push_back(new VisualizeCommand(sphere, color));
}

void CollisionVisualizer::PrivProcessCollisionVisuals()
{
	std::list<VisualizeCommand*>::iterator it = showSphereRequests.begin();
	while (it != showSphereRequests.end())
	{
		(*it)->Execute();
		VisualizeCommand* tempCmd = *it;
		it = showSphereRequests.erase(it);
		delete tempCmd;
	}
}

void CollisionVisualizer::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}