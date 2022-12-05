#include "GraphicsObject_ColorFlat.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>
#include "ShaderManager.h"
#include "GPUController.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

GraphicsObject_ColorFlat::GraphicsObject_ColorFlat(Model* mod, const Vect& color)
	:pShader(static_cast<ShaderColor*>(ShaderManager::GetShader("colorFlat"))),
	meshColors(new Vect[mod->GetMeshCount()]),
	world(Matrix(IDENTITY))
{
	SetModel(mod);

	for (int i = 0; i < mod->GetMeshCount(); i++)
		meshColors[i] = color;
}

GraphicsObject_ColorFlat::~GraphicsObject_ColorFlat()
{
	delete[] meshColors;
}

void GraphicsObject_ColorFlat::SetColor(const Vect& col)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		meshColors[i] = col;
}

void GraphicsObject_ColorFlat::SetColor(const Vect& col, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	meshColors[meshnum] = col;
}

void GraphicsObject_ColorFlat::SetWorld(const Matrix& m)
{ 
	world = m;
}

void GraphicsObject_ColorFlat::RenderSolid()
{
	GPUController::SetRasterizerSolid();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldColor(world, meshColors[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}

void GraphicsObject_ColorFlat::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldColor(world, meshColors[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}