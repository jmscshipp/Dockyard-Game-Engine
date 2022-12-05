#include "GraphicsObject_TextureOutlined.h"
#include "GraphicsCore.h"
#include "ShaderManager.h"
#include "GPUController.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"

GraphicsObject_TextureOutlined::GraphicsObject_TextureOutlined(Model* model, Texture* tex, const Vect& colorForOutline, float sizeForOutline)
	:pObjectShader(static_cast<ShaderTexture*>(ShaderManager::GetShader("textureFlat"))),
	meshCount(model->GetMeshCount()),
	textures(new Texture* [meshCount]),
	pOutlineShader(static_cast<ShaderOutline*>(ShaderManager::GetShader("textureOutline"))),
	outlineColor(colorForOutline),
	outlineSize(sizeForOutline),
	world(Matrix(IDENTITY))
{
	GraphicsObject_Base::SetModel(model);

	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}

GraphicsObject_TextureOutlined::~GraphicsObject_TextureOutlined()
{
	delete[] textures;
}

// set all textures as same
void GraphicsObject_TextureOutlined::SetTexture(Texture* tex)
{
	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}
// set specific tex
void GraphicsObject_TextureOutlined::SetTexture(Texture* tex, int meshIndex)
{
	textures[meshIndex] = tex;
}

void GraphicsObject_TextureOutlined::SetOutlineColor(const Vect& newColor)
{
	outlineColor = newColor;
}

void GraphicsObject_TextureOutlined::SetOutlineSize(float newSize)
{
	outlineSize = newSize;
}

void GraphicsObject_TextureOutlined::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicsObject_TextureOutlined::RenderSolid()
{
	GPUController::SetRasterizerFrontcullSolid();

	// render outline
	pOutlineShader->SetToContext(GPUController::GetContext());
	pOutlineShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());
	pModel->SetToContext(pOutlineShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pOutlineShader->SendWorldColorSize(world, outlineColor, outlineSize); // move out of loop
		pModel->RenderMesh(pOutlineShader->GetContext(), i);
	}

	// render object
	GPUController::SetRasterizerSolid();
	
	pObjectShader->SetToContext(GPUController::GetContext());
	pObjectShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());
	
	pObjectShader->SendWorld(world);
	pModel->SetToContext(pObjectShader->GetContext());
	
	for (int i = 0; i < meshCount; i++)
	{
		pObjectShader->SetTextureResourceAndSampler(textures[i]);
		pModel->RenderMesh(pObjectShader->GetContext(), i);
	}
}

void GraphicsObject_TextureOutlined::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pObjectShader->SetToContext(GPUController::GetContext());
	pObjectShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());

	pObjectShader->SendWorld(world);
	pModel->SetToContext(pObjectShader->GetContext());

	for (int i = 0; i < meshCount; i++)
	{
		pObjectShader->SetTextureResourceAndSampler(textures[i]);
		pModel->RenderMesh(pObjectShader->GetContext(), i);
	}
}