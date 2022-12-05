#ifndef _Terrain
#define _Terrain

#include "Matrix.h"
#include <d3d11.h>
#include "TerrainBase.h"

// forward declaration
class Model;
class GraphicsObject_TextureOutlined;
class CollisionVolumeAABB;
class Collidable;

class Terrain : public TerrainBase, public Align16
{
public:
	Terrain() = delete;
	Terrain(LPCWSTR heightmapFile, std::string textureName, float vertexNum, float cellSize, float maxheight, float ytrans, int RepeatU, int RepeatV);
	Terrain(const Terrain&) = delete;
	Terrain(Terrain&&) = delete;
	Terrain& operator=(const Terrain&) = delete;
	Terrain& operator=(Terrain&&) = delete;
	~Terrain();

	void Render() const override;
	Model* GetModel() const override;
	CollisionVolumeAABB* GetCellAtPosition(const Vect& pos) const override;
	Vect& GetPositionAtPoint(const Vect& point) override;
	Vect& GetNormalAtPoint(const Vect& point) override;
	void Intersect(Collidable* col) const override;

private:
	Model* pModTerrain;
	GraphicsObject_TextureOutlined* gObjOutlined;

	// AABB stuff
	Vect cellOrigin;
	float cellSize;
	int cellsPerSide;
	CollisionVolumeAABB* cellAABBs;

	// helper functions
	void UpdateInfoAtPoint(const Vect& pos);
	CollisionVolumeAABB* GetCellAtIndices(int xIndex, int zIndex) const;
	int GetVertexIndex(int sideLength, int i, int j) const;
	int GetTexelIndex(size_t pixelWidth, int sideLength, int i, int j) const;
};

#endif _Terrain