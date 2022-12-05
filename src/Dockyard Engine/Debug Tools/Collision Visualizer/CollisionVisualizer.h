#ifndef _CollisionVisualizer
#define _CollisionVisualizer

#include "CollisionVolume.h"
#include "ColorLibrary.h"
#include <list>

// forward declaration
class GraphicsObject_ColorFlat;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class VisualizeCommandBase;
class VisualizeCommandPool;

class CollisionVisualizer
{
private:
	static CollisionVisualizer* instance; // set up as singleton

	// big four
	CollisionVisualizer();
	CollisionVisualizer(const CollisionVisualizer&) = delete;
	CollisionVisualizer& operator = (const CollisionVisualizer&) = delete;
	~CollisionVisualizer();

	static CollisionVisualizer& Instance()
	{
		if (!instance)
			instance = new CollisionVisualizer();
		return *instance;
	};

	//using CommandList = std::list<VisualizeCommand*>;
	std::list<VisualizeCommandBase*> showColVolumeRequests;

	// Bsphere
	void NonstaticRenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color);
	static void RenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color) { Instance().NonstaticRenderBSphere(sphere, color); }
	void PrivShowBSphere(const CollisionVolumeBSphere& sphere, const Vect& color);
	// AABB
	void NonstaticRenderAABB(const CollisionVolumeAABB& box, const Vect& color);
	static void RenderAABB(const CollisionVolumeAABB& box, const Vect& color) { Instance().NonstaticRenderAABB(box, color); }
	void PrivShowAABB(const CollisionVolumeAABB& box, const Vect& color);
	// OBB
	void NonstaticRenderOBB(const CollisionVolumeOBB& box, const Vect& color);
	static void RenderOBB(const CollisionVolumeOBB& box, const Vect& color) { Instance().NonstaticRenderOBB(box, color); }
	void PrivShowOBB(const CollisionVolumeOBB& box, const Vect& color);
	// box at position
	void NonstaticRenderBoxAtPos(float x, float y, float z, const Vect& color);
	static void RenderBoxAtPos(float x, float y, float z, const Vect& color) { Instance().NonstaticRenderBoxAtPos(x, y, z, color); };
	void PrivShowBoxAtPos(float x, float y, float z, const Vect& color);
	// line
	void NonstaticRenderLine(const Vect& pos, const Vect& rotDir, const Vect& color);
	static void RenderLine(const Vect& pos, const Vect& rotDir, const Vect& color) { Instance().NonstaticRenderLine(pos, rotDir, color); };
	void PrivShowLine(const Vect& pos, const Vect& rotDir, const Vect& color);

	void PrivProcessCollisionVisuals();
	static void ProcessCollisionVisuals() { Instance().PrivProcessCollisionVisuals(); };
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	VisualizeCommandPool* cmdPool;
	GraphicsObject_ColorFlat* unitSphere;
	GraphicsObject_ColorFlat* unitBox;
	static Vect DEFAULT_COLOR;

	friend class CollisionVisualizerAttorney;

public:
	static void ShowCollisionVolume(const CollisionVolume& colVolume, const Vect& color = DEFAULT_COLOR) { colVolume.DebugView(color); }
	static void ShowBSphere(const CollisionVolumeBSphere& sphere, const Vect& color) { Instance().PrivShowBSphere(sphere, color); }
	static void ShowAABB(const CollisionVolumeAABB& box, const Vect& color) { Instance().PrivShowAABB(box, color); }
	static void ShowOBB(const CollisionVolumeOBB& box, const Vect& color) { Instance().PrivShowOBB(box, color); }
	static void ShowBoxAtPos(float x, float y, float z, const Vect& color = DEFAULT_COLOR) { Instance().PrivShowBoxAtPos(x, y, z, color); };
	static void ShowLine(const Vect& pos, const Vect& rotDir, const Vect& color = DEFAULT_COLOR) { Instance().PrivShowLine(pos, rotDir, color); };
};

#endif