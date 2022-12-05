#include "TerrainManager.h"

TerrainManager* TerrainManager::instance = nullptr;

TerrainManager::TerrainManager()
{

}

TerrainManager::~TerrainManager()
{
	for (std::pair<std::string, Terrain*> element : loadedTerrains)
		delete(element.second);
}

void TerrainManager::PrivLoadTerrain(std::string terrainName, std::wstring heightMapFileLocation, std::string textureName, float vertexNum, float _cellSize, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	if (loadedTerrains.count(terrainName) > 0) // if a texture with this name has already been loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is already a loaded terrain named " + terrainName + " !!!\n");
	}
	else
	{
		LPCWSTR path = heightMapFileLocation.c_str();
		Terrain* newTerrain = new Terrain(path, textureName, vertexNum, _cellSize, maxheight, ytrans, RepeatU, RepeatV);
		loadedTerrains.emplace(terrainName, newTerrain);
	}
}

Terrain* TerrainManager::PrivGetTerrain(std::string terrainName)
{
	std::map<std::string, Terrain*>::const_iterator findResult = loadedTerrains.find(terrainName);
	if (findResult == loadedTerrains.end()) // if we have no terrain of this name loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is no loaded terrain named " + terrainName + " !!!\n");
		return nullptr;
	}
	else
	{
		return findResult->second;
	}
}

void TerrainManager::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}