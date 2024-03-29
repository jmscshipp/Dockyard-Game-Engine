#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
	//Model* defaultSpriteModel = new Model(Model::PreMadeModels::UnitSquareXY);
	//loadedModels.emplace("defaultSpriteModel", defaultSpriteModel);

	Model* unitSphere = new Model(Model::PreMadeModels::UnitSphere);
	loadedModels.emplace("UnitSphere", unitSphere);

	Model* unitBox = new Model(Model::PreMadeModels::UnitBox);
	loadedModels.emplace("UnitBox", unitBox);

	Model* unitSquare2D = new Model(Model::PreMadeModels::UnitSquare2D);
	loadedModels.emplace("UnitSquare2D", unitSquare2D);
}

ModelManager::~ModelManager()
{
	for (std::pair<std::string, Model*> element : loadedModels)
		delete(element.second);
}

void ModelManager::PrivLoadModel(std::string modelName, std::string modelFileLocation)
{
	if (loadedModels.count(modelName) > 0) // if a model with this name has already been loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is already a loaded model named " + modelName + " !!!\n");
	}
	else
	{
		Model* newLoadedModel = new Model((defaultPath + modelFileLocation).c_str());
		loadedModels.emplace(modelName, newLoadedModel);
	}
}

void ModelManager::PrivLoadModel(std::string modelName, Model::PreMadeModels premadeModel)
{
	if (loadedModels.count(modelName) > 0) // if a model with this name has already been loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is already a loaded model named " + modelName + " !!!\n");
	}
	else
	{
		Model* newLoadedModel = new Model(premadeModel);
		loadedModels.emplace(modelName, newLoadedModel);
	}
}

Model* ModelManager::PrivGetModel(std::string modelName)
{
	std::map<std::string, Model*>::const_iterator findResult = loadedModels.find(modelName);
	if (findResult == loadedModels.end()) // if we have no model of this name loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is no loaded model named " + modelName + " !!!\n");
		return nullptr;
	}
	else
		return findResult->second;
}

void ModelManager::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}