#ifndef _TerrainManager
#define _TerrainManager

#include "GraphicsCore.h"
#include <map>

class TerrainManager
{
private:
	static TerrainManager* instance; // set up as singleton

	// big four
	TerrainManager();
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator = (const TerrainManager&) = delete;
	~TerrainManager();

	static TerrainManager& Instance()
	{
		if (!instance)
			instance = new TerrainManager();
		return *instance;
	};

	void PrivLoadTerrain(std::string terrainName, std::wstring heightMapFileLocation, std::string textureName, float vertexNum, float _cellSize, float maxheight, float ytrans, int RepeatU, int RepeatV);
	Terrain* PrivGetTerrain(std::string terrainName);

	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	// to allow Dockyard to Delete() singleton
	friend class TerrainManagerAttorney;

	const std::wstring defaultPath = L"../Assets/Textures/"; // need to include '/' for file path
	std::map<std::string, Terrain*> loadedTerrains;

public:
	static void LoadTerrain(std::string terrainName, std::wstring heightMapFileLocation, std::string textureName, float vertexNum, float _cellSize, float maxheight, float ytrans, int RepeatU, int RepeatV) 
	{ Instance().PrivLoadTerrain(terrainName, heightMapFileLocation, textureName, vertexNum, _cellSize, maxheight, ytrans, RepeatU, RepeatV); }
	static Terrain* GetTerrain(std::string terrainName) { return Instance().PrivGetTerrain(terrainName); }
};

#endif