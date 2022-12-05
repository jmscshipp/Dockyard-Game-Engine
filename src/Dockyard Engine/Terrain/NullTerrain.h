#ifndef _NullTerrain
#define _NullTerrain

#include "TerrainBase.h"

// forward declaration
class Model;
class GraphicsObject_TextureFlat;
class CollisionVolumeAABB;
class Collidable;
class Vect;

class NullTerrain : public TerrainBase
{
public:
	NullTerrain() = default;
	NullTerrain(const NullTerrain&) = delete;
	NullTerrain(NullTerrain&&) = delete;
	NullTerrain& operator=(const NullTerrain&) = delete;
	NullTerrain& operator=(NullTerrain&&) = delete;
	~NullTerrain() = default;

	void Render() const override {};
	Model* GetModel() const override { return nullptr; };
	CollisionVolumeAABB* GetCellAtPosition(const Vect& pos) const override { return nullptr; };
	Vect& GetPositionAtPoint(const Vect& point) override { return positionAtPoint; };
	Vect& GetNormalAtPoint(const Vect& point) override { return normalAtPoint; };
	void Intersect(Collidable* col) const override {};
};

#endif _NullTerrain