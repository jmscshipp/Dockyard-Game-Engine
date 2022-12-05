#include "GraphicsObject_TextureLight.h"
#include "ShaderTextureLight.h"
#include "Model.h"
#include "GPUController.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"
#include "ColorLibrary.h"

GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model* model, Texture* tex)
	:pShader(static_cast<ShaderTextureLight*>(ShaderManager::GetShader("textureLight"))),
	meshCount(model->GetMeshCount()),
	textures(new Texture*[meshCount]),
	materials(new Material[meshCount]),
	world(Matrix(IDENTITY))
{
	GraphicsObject_Base::SetModel(model);

	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;

	for (int i = 0; i < meshCount; i++)
	{
		materials[i].ambient = Vect(1, 1, 1, 100);
		materials[i].diffuse = Vect(1, 1, 1, 100);
		materials[i].specular = Vect(1, 1, 1, 100);
	}
	SetFogValues(0.0f, 0.0f, Colors::White);
}

GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
{
	delete[] textures;
	delete[] materials;
}

// set all textures to same
void GraphicsObject_TextureLight::SetTexture(Texture* tex)
{
	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}
// set specific tex
void GraphicsObject_TextureLight::SetTexture(Texture* tex, int meshIndex)
{
	textures[meshIndex] = tex;
}

// setting all materials
void GraphicsObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < meshCount; i++)
	{
		materials[i].ambient = amb;
		materials[i].diffuse = dif;
		materials[i].specular = sp;
	}
}
// setting specific mat
void GraphicsObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	materials[num].ambient = amb;
	materials[num].diffuse = dif;
	materials[num].specular = sp;
}

void GraphicsObject_TextureLight::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicsObject_TextureLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SetDirectionalLightParameters(dir, amb, dif, sp);
}

void GraphicsObject_TextureLight::SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SetPointLightParameters(index, pos, r, att, amb, dif, sp);
}

void GraphicsObject_TextureLight::SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SetSpotLightParameters(index, pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicsObject_TextureLight::SetFogValues(const float& fogStart, const float& fogRange, const Vect& fogColor)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SendFogValues(fogStart, fogRange, fogColor);
}

void GraphicsObject_TextureLight::RenderSolid()
{
	GPUController::SetRasterizerSolid();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());
	
	Vect camPos;
	SceneManager::GetCurrentScene()->GetCurrentCamera()->getPos(camPos);
	pShader->SendLightParameters(camPos);
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < meshCount; i++)
	{
		pShader->SetTextureResourceAndSampler(textures[i]);
		pShader->SendWorldAndMaterial(world, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}

void GraphicsObject_TextureLight::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCurrentCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCurrentCamera()->getProjMatrix());

	Vect camPos;
	SceneManager::GetCurrentScene()->GetCurrentCamera()->getPos(camPos);
	pShader->SendLightParameters(camPos);
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < meshCount; i++)
	{
		pShader->SetTextureResourceAndSampler(textures[i]);
		pShader->SendWorldAndMaterial(world, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}