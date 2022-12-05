#include "GraphicsObject_TextureFlat.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderManager.h"
#include "GPUController.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

GraphicsObject_TextureFlat::GraphicsObject_TextureFlat(Model* model, Texture* tex)
	:pShader(static_cast<ShaderTexture*>(ShaderManager::GetShader("textureFlat"))),
	meshCount(model->GetMeshCount()),
	textures(new Texture*[meshCount]),
	world(Matrix(IDENTITY))
{
	GraphicsObject_Base::SetModel(model);

	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}

GraphicsObject_TextureFlat::~GraphicsObject_TextureFlat()
{
	delete[] textures;
}

// set all textures as same
void GraphicsObject_TextureFlat::SetTexture(Texture* tex)
{
	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}
// set specific tex
void GraphicsObject_TextureFlat::SetTexture(Texture* tex, int meshIndex)
{
	textures[meshIndex] = tex;
}

void GraphicsObject_TextureFlat::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicsObject_TextureFlat::RenderSolid()
{
	GPUController::SetRasterizerSolid();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());

	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < meshCount; i++)
	{
		pShader->SetTextureResourceAndSampler(textures[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}

void GraphicsObject_TextureFlat::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());

	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < meshCount; i++)
	{
		pShader->SetTextureResourceAndSampler(textures[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}