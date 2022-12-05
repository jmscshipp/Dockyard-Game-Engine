#include "ShaderManager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager()
{
	//defaultSpriteShader = new Shader((defaultPath + "SpriteRender").c_str());
	//loadedShaders.emplace(spriteShaderDefaultKey, defaultSpriteShader);
}

ShaderManager::~ShaderManager()
{
	for (std::pair<std::string, Shader*> element : loadedShaders)
		delete(element.second);
}

//void ShaderManager::PrivLoadShader(std::string shaderName, std::string shaderFileLocation)
//{
//	if (loadedShaders.count(shaderName) > 0) // if a shader with this name has already been loaded
//	{
//		// THROW ERROR
//		throw("!!! ERROR: There is already a loaded shader named " + shaderName + " !!!\n");
//	}
//	else
//	{
//		ShaderObject* newLoadedShader = new ShaderObject((defaultPath + shaderFileLocation).c_str());
//		loadedShaders.emplace(shaderName, newLoadedShader);
//	}
//}
void ShaderManager::PrivLoadShader(std::string shaderName, Shader* shader)
{
	if (loadedShaders.count(shaderName) > 0) // if a shader with this name has already been loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is already a loaded shader named " + shaderName + " !!!\n");
	}
	else
	{
		loadedShaders.emplace(shaderName, shader);
	}
}

Shader* ShaderManager::PrivGetShader(std::string shaderName)
{
	std::map<std::string, Shader*>::const_iterator findResult = loadedShaders.find(shaderName);
	if (findResult == loadedShaders.end()) // if we have no shader of this name loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is no loaded shader named " + shaderName + " !!!\n");
		return nullptr;
	}
	else
	{
		return findResult->second;
	}
}

void ShaderManager::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}