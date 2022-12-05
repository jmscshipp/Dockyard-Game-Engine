#include "GraphicsObject_ColorLight.h"
#include "ShaderColorLight.h"
#include "Model.h"
#include "ShaderManager.h"
#include "GPUController.h"

GraphicsObject_ColorLight::GraphicsObject_ColorLight(Model* model)
	:pShader(static_cast<ShaderColorLight*>(ShaderManager::GetShader("colorLight")))
{
	GraphicsObject_Base::SetModel(model);
	world = Matrix(IDENTITY);
	meshCount = model->GetMeshCount();

	materials = new Material[meshCount];
}

GraphicsObject_ColorLight::~GraphicsObject_ColorLight()
{
	delete[] materials;
}

// setting all materials
void GraphicsObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < meshCount; i++) 
	{
		materials[i].ambient = amb;
		materials[i].diffuse = dif;
		materials[i].specular = sp;
	}
}
// setting specific mat
void GraphicsObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	materials[num].ambient = amb;
	materials[num].diffuse = dif;
	materials[num].specular = sp;
}

void GraphicsObject_ColorLight::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}

void GraphicsObject_ColorLight::RenderSolid()
{
	GPUController::SetRasterizerSolid();

	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < meshCount; i++)
	{
		pShader->SendWorldAndMaterial(world, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->Render(pShader->GetContext());
	}
}

void GraphicsObject_ColorLight::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < meshCount; i++)
	{
		pShader->SendWorldAndMaterial(world, materials[i].ambient, materials[i].diffuse, materials[i].specular);
		pModel->Render(pShader->GetContext());
	}
}