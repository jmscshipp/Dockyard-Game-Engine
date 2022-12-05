#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (std::pair<std::string, Texture*> element : loadedTextures)
		delete(element.second);
}

void TextureManager::PrivLoadTexture(std::string textureName, std::wstring textureFileLocation)
{
	if (loadedTextures.count(textureName) > 0) // if a texture with this name has already been loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is already a loaded texture named " + textureName + " !!!\n");
	}
	else
	{
		std::wstring strPath = defaultPath + textureFileLocation;
		LPCWSTR path = strPath.c_str();
		Texture* newLoadedTexture = new Texture(path);
		loadedTextures.emplace(textureName, newLoadedTexture);
	}
}

Texture* TextureManager::PrivGetTexture(std::string textureName)
{
	std::map<std::string, Texture*>::const_iterator findResult = loadedTextures.find(textureName);
	if (findResult == loadedTextures.end()) // if we have no texture of this name loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is no loaded texture named " + textureName + " !!!\n");
		return nullptr;
	}
	else
	{
		return findResult->second;
	}
}

void TextureManager::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}