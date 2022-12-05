#include "GraphicsObject_Sprite.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "GPUController.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

GraphicsObject_Sprite::GraphicsObject_Sprite(Texture* _tex)
	:pShader(static_cast<ShaderTexture*>(ShaderManager::GetShader("textureFlat"))),
	tex(_tex),
	world(Matrix(IDENTITY)),
	position(Vect(0, 0, 0))
{
	GraphicsObject_Base::SetModel(ModelManager::GetModel("UnitSquare2D"));
}

GraphicsObject_Sprite::~GraphicsObject_Sprite()
{
}

void GraphicsObject_Sprite::SetTexture(Texture* _tex)
{
	tex = _tex;
}

void GraphicsObject_Sprite::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}
void GraphicsObject_Sprite::SetPosition(const Vect& pos)
{
	position = pos;
}

const Vect& GraphicsObject_Sprite::GetPosition()
{
	return position;
}

void GraphicsObject_Sprite::RenderSolid()
{
	GPUController::SetRasterizerSolid();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetDefaultOrthoCam()->getViewMatrix(), SceneManager::GetCurrentScene()->GetDefaultOrthoCam()->getProjMatrix());
	//pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());

	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	pShader->SetTextureResourceAndSampler(tex);
	pModel->Render(pShader->GetContext());
}

void GraphicsObject_Sprite::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetDefaultOrthoCam()->getViewMatrix(), SceneManager::GetCurrentScene()->GetDefaultOrthoCam()->getProjMatrix());

	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	pShader->SetTextureResourceAndSampler(tex);
	pModel->Render(pShader->GetContext());
}