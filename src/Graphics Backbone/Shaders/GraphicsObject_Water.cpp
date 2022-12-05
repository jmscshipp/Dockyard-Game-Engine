#include "GraphicsObject_Water.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderManager.h"
#include "GPUController.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"
#include "TimeManager.h"

GraphicsObject_Water::GraphicsObject_Water(Texture* _tex, float vertexNum, float cellSize, float textureRepeatInterval)
	:pShader(static_cast<ShaderWater*>(ShaderManager::GetShader("water"))),
	tex(_tex),
	world(Matrix(IDENTITY)),
	pModel(nullptr)
{
	int vertNum = static_cast<int>(vertexNum * vertexNum);
	StandardVertex* verts = new StandardVertex[vertNum];

	int triNum = (vertexNum - 1) * (vertexNum - 1) * 2;
	TriangleByIndex* tris = new TriangleByIndex[triNum];

	float texRepeat = textureRepeatInterval / (vertexNum - 1);

	// setting up vertices
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			float x = (i - vertexNum / 2) * cellSize;
			float y = 0;
			float z = (j - vertexNum / 2) * cellSize;
			verts[GetVertexIndex(vertexNum, i, j)].set(x, y, z, texRepeat * i, texRepeat * j);
		}
	}
	
	// since this shader doesn't have lighting, we don't really care about normals

	// setting up triangles and aabb array
	int triangleIndex = 0;
	for (int i = 0; i < vertexNum - 1; i++)
	{
		for (int j = 0; j < vertexNum - 1; j++)
		{
			// indices for tri corners
			int corner0 = static_cast<int>(j + (vertexNum * i) + 1);
			int corner1 = static_cast<int>(j + vertexNum + (vertexNum * i));
			int corner2 = static_cast<int>(j + (vertexNum * i));
			int corner3 = static_cast<int>(j + vertexNum + (vertexNum * i) + 1);

			// setting tris
			tris[triangleIndex++].set(corner0, corner1, corner2);
			tris[triangleIndex++].set(corner0, corner3, corner1);
		}
	}

	pModel = new Model(verts, vertNum, tris, triNum);

	delete[] verts;
	delete[] tris;

	GraphicsObject_Base::SetModel(pModel);
}

int GraphicsObject_Water::GetVertexIndex(int sideLength, int i, int j) const
{
	return i * sideLength + j;
}

GraphicsObject_Water::~GraphicsObject_Water()
{
	delete pModel;
}

// set all textures as same
void GraphicsObject_Water::SetTexture(Texture* _tex)
{
	tex = _tex;
}

void GraphicsObject_Water::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicsObject_Water::RenderSolid()
{
	GPUController::SetRasterizerSolid();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());

	pShader->SendWorldColorSize(world, Vect(0.34f, 1.3f, 40.4f), TimeManager::GetTime());
	pModel->SetToContext(pShader->GetContext());

	pShader->SetTextureResourceAndSampler(tex);
	pModel->Render(GPUController::GetContext());
}

void GraphicsObject_Water::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());

	//pShader->SendWorldAndTime(world, TimeManager::GetTime());
	pModel->SetToContext(pShader->GetContext());

	pShader->SetTextureResourceAndSampler(tex);
	pModel->Render(GPUController::GetContext());
}

