#include "CollisionVisualizer.h"
#include "GraphicsObject_ColorFlat.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ColorLibrary.h"
#include "SceneManager.h"
#include "Scene.h"
#include "VisualizeCommandBSphere.h"
#include "VisualizeCommandAABB.h"
#include "VisualizeCommandOBB.h"
#include "VisualizeCommandBoxAtPoint.h"
#include "VisualizeCommandLine.h"
#include "VisualizeCommandPool.h"

CollisionVisualizer* CollisionVisualizer::instance = nullptr;
Vect CollisionVisualizer::DEFAULT_COLOR = Colors::LimeGreen;

CollisionVisualizer::CollisionVisualizer()
{
	cmdPool = new VisualizeCommandPool();
	unitSphere = new GraphicsObject_ColorFlat(ModelManager::GetModel("UnitSphere"), DEFAULT_COLOR);
	unitBox = new GraphicsObject_ColorFlat(ModelManager::GetModel("UnitBox"), DEFAULT_COLOR);
	showColVolumeRequests = {};
}

CollisionVisualizer::~CollisionVisualizer()
{
	delete cmdPool;
	delete unitSphere;
	delete unitBox;
	for (std::list<VisualizeCommandBase*>::iterator it = showColVolumeRequests.begin(); it != showColVolumeRequests.end(); it++)
		delete* it;
}

// BSPHERE
void CollisionVisualizer::PrivShowBSphere(const CollisionVolumeBSphere& sphere, const Vect& color)
{
	VisualizeCommandBSphere* cmd = cmdPool->GetBSphereCommand();
	cmd->Initialize(sphere, color);
	showColVolumeRequests.push_back(cmd);
}

void CollisionVisualizer::NonstaticRenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color)
{
	float matScale = sphere.GetRadius();
	Vect center = sphere.GetCenter();
	// Adjust the Bounding Sphere's position and scale to fit the object's center and scale
	Matrix world = Matrix(SCALE, matScale, matScale, matScale) * Matrix(TRANS, center);

	unitSphere->SetWorld(world);
	unitSphere->SetColor(color);
	unitSphere->RenderWireframe();
}

// AABB
void CollisionVisualizer::PrivShowAABB(const CollisionVolumeAABB& box, const Vect& color)
{
	VisualizeCommandAABB* cmd = cmdPool->GetAABBCommand();
	cmd->Initialize(box, color);
	showColVolumeRequests.push_back(cmd);
}

void CollisionVisualizer::CollisionVisualizer::NonstaticRenderAABB(const CollisionVolumeAABB& box, const Vect& color)
{
	Vect scale = box.GetMax() - box.GetMin();
	Vect center = 0.5f * (box.GetMax() + box.GetMin());
	// adjust unit box world matrix according to s and t
	Matrix world = Matrix(SCALE, scale) * Matrix(TRANS, center);

	unitBox->SetWorld(world);
	unitBox->SetColor(color);
	unitBox->RenderWireframe();
}

// OBB
void CollisionVisualizer::PrivShowOBB(const CollisionVolumeOBB& box, const Vect& color)
{
	VisualizeCommandOBB* cmd = cmdPool->GetOBBCommand();
	cmd->Initialize(box, color);
	showColVolumeRequests.push_back(cmd);
}

void CollisionVisualizer::NonstaticRenderOBB(const CollisionVolumeOBB& box, const Vect& color)
{
	Vect scale = box.GetMax() - box.GetMin();
	Vect center = 0.5f * (box.GetMax() + box.GetMin());
	// adjust unit box world matrix according to s and t
	Matrix world = Matrix(SCALE, scale) * Matrix(TRANS, center);
	world *= box.GetWorld();
	unitBox->SetWorld(world);
	unitBox->SetColor(color);
	unitBox->RenderWireframe();
}

// show box at point
void CollisionVisualizer::PrivShowBoxAtPos(float x, float y, float z, const Vect& color)
{
	VisualizeCommandBoxAtPoint* cmd = cmdPool->GetBoxAtPointCommand();
	cmd->Initialize(x, y, z, color);
	showColVolumeRequests.push_back(cmd);
}

void CollisionVisualizer::NonstaticRenderBoxAtPos(float x, float y, float z, const Vect& color)
{
	Matrix world = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, x, y, z);
	unitBox->SetWorld(world);
	unitBox->SetColor(color);
	unitBox->RenderWireframe();
}

// line
void CollisionVisualizer::PrivShowLine(const Vect& pos, const Vect& rotDir, const Vect& color)
{
	VisualizeCommandLine* cmd = cmdPool->GetLineCommand();
	cmd->Initialize(pos, rotDir, color);
	showColVolumeRequests.push_back(cmd);
}

void CollisionVisualizer::NonstaticRenderLine(const Vect& pos, const Vect& rotDir, const Vect& color)
{
	const float length = 10.0f;

	Vect normalizedDir = rotDir.getNorm();
	Vect center = pos + (0.5f * length) * normalizedDir;
	Vect up = normalizedDir.cross(Vect(0, 1, 0)).cross(normalizedDir);

	Matrix world = Matrix(SCALE, 0.2f, 0.2f, length) * Matrix(RotOrientType::ROT_ORIENT, rotDir, up) * Matrix(TRANS, center);
	unitBox->SetWorld(world);
	unitBox->SetColor(color);
	unitBox->RenderWireframe();
}

void CollisionVisualizer::PrivProcessCollisionVisuals()
{
	std::list<VisualizeCommandBase*>::iterator it = showColVolumeRequests.begin();
	while (it != showColVolumeRequests.end())
	{
		(*it)->Execute(cmdPool);
		it = showColVolumeRequests.erase(it);
	}
}

void CollisionVisualizer::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}