#ifndef _TerrainBase
#define _TerrainBase

// forward declaration
class Model;
class GraphicsObject_TextureFlat;
class CollisionVolumeAABB;
class Collidable;

class TerrainBase
{
public:
	TerrainBase() = default;
	TerrainBase(const TerrainBase&) = delete;
	TerrainBase(TerrainBase&&) = delete;
	TerrainBase& operator=(const TerrainBase&) = delete;
	TerrainBase& operator=(TerrainBase&&) = delete;
	~TerrainBase() = default;

	virtual void Render() const = 0;
	virtual Model* GetModel() const = 0;
	virtual CollisionVolumeAABB* GetCellAtPosition(const Vect& pos) const = 0;
	virtual Vect& GetPositionAtPoint(const Vect& point) = 0;
	virtual Vect& GetNormalAtPoint(const Vect& point) = 0;
	virtual void Intersect(Collidable* col) const = 0;

protected:
	// these get updated and returned when requested
	Vect positionAtPoint;
	Vect normalAtPoint;
};

#endif _TerrainBase