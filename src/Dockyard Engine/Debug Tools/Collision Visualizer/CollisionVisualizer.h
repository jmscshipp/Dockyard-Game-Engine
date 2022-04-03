#ifndef _CollisionVisualizer
#define _CollisionVisualizer

#include "AzulCore.h"
#include <list>

// forward declaration
class GraphicsObject_WireframeConstantColor;
class CollisionVolumeBSphere;
class VisualizeCommand;

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
	std::list<VisualizeCommand*> showSphereRequests;

	void NonstaticRenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color);
	static void RenderBSphere(const CollisionVolumeBSphere& sphere, const Vect& color) { Instance().NonstaticRenderBSphere(sphere, color); }
	void PrivShowBSphere(const CollisionVolumeBSphere& sphere, const Vect& color);
	void PrivProcessCollisionVisuals();
	static void ProcessCollisionVisuals() { Instance().PrivProcessCollisionVisuals(); };
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	GraphicsObject_WireframeConstantColor* wireframeUnitSphere;
	static Vect DEFAULT_COLOR;

	friend class CollisionVisualizerAttorney;

public:
	static void ShowBSphere(const CollisionVolumeBSphere& sphere, const Vect& color = DEFAULT_COLOR) { Instance().PrivShowBSphere(sphere, color); }
};

#endif