#include "GraphicsObject_Cartoon.h"
#include "ShaderCartoon.h"
#include "Model.h"
#include "GPUController.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"
#include "ColorLibrary.h"

GraphicsObject_Cartoon::GraphicsObject_Cartoon(Model* model, const Vect& color0, const Vect& color1, const Vect& color2, Texture* tex)
	:pShader(static_cast<ShaderCartoon*>(ShaderManager::GetShader("cartoon"))),
	meshCount(model->GetMeshCount()),
	textures(new Texture* [meshCount]),
	materials(new Material[meshCount]),
	world(Matrix(IDENTITY)),
	Color0(color0),
	Color1(color1),
	Color2(color2)
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

GraphicsObject_Cartoon::~GraphicsObject_Cartoon()
{
	delete[] textures;
	delete[] materials;
}

// set all textures to same
void GraphicsObject_Cartoon::SetTexture(Texture* tex)
{
	for (int i = 0; i < meshCount; i++)
		textures[i] = tex;
}
// set specific tex
void GraphicsObject_Cartoon::SetTexture(Texture* tex, int meshIndex)
{
	textures[meshIndex] = tex;
}

// setting all materials
void GraphicsObject_Cartoon::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < meshCount; i++)
	{
		materials[i].ambient = amb;
		materials[i].diffuse = dif;
		materials[i].specular = sp;
	}
}
// setting specific mat
void GraphicsObject_Cartoon::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	materials[num].ambient = amb;
	materials[num].diffuse = dif;
	materials[num].specular = sp;
}

void GraphicsObject_Cartoon::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicsObject_Cartoon::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SetDirectionalLightParameters(dir, amb, dif, sp);
}

void GraphicsObject_Cartoon::SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SetPointLightParameters(index, pos, r, att, amb, dif, sp);
}

void GraphicsObject_Cartoon::SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SetSpotLightParameters(index, pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicsObject_Cartoon::SetFogValues(const float& fogStart, const float& fogRange, const Vect& fogColor)
{
	pShader->SetToContext(GPUController::GetContext());
	pShader->SendFogValues(fogStart, fogRange, fogColor);
}

void GraphicsObject_Cartoon::RenderSolid()
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
		pShader->SendWorldMatColors(world, Color0, Color1, Color2, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}

void GraphicsObject_Cartoon::RenderWireframe()
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
		pShader->SendWorldMatColors(world, Color0, Color1, Color2, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}