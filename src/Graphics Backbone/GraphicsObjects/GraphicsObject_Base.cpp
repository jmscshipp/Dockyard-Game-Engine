#include "GraphicsObject_Base.h"
#include "Model.h"
#include <assert.h>

GraphicsObject_Base::GraphicsObject_Base()
{
	pModel = nullptr;
}

void GraphicsObject_Base::SetModel(Model* mod)
{
	pModel = mod;
}

Model* GraphicsObject_Base::GetModel()
{
	return pModel;
}