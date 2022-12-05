#ifndef _GraphicsObject_Water
#define _GraphicsObject_Water

#include "GraphicsObject_Base.h"

// forward declarations
class ShaderWater;
class Texture;

class GraphicsObject_Water : public GraphicsObject_Base
{
public:
	GraphicsObject_Water(Texture* tex, float vertexNum, float cellSize, float textureRepeatInterval);
	GraphicsObject_Water(const GraphicsObject_Water&) = delete;				 // Copy constructor
	GraphicsObject_Water(GraphicsObject_Water&&) = default;                  // Move constructor
	GraphicsObject_Water& operator=(const GraphicsObject_Water&) = default;  // Copy assignment operator
	GraphicsObject_Water& operator=(GraphicsObject_Water&&) = default;       // Move assignment operator
	~GraphicsObject_Water();		  												 // Destructor

	// sets for all meshes
	void SetTexture(Texture* tex);
	void SetWorld(const Matrix& worldMat);


	virtual void RenderSolid() override;
	virtual void RenderWireframe() override;

protected:
	ShaderWater* pShader;
	Texture* tex;
	Matrix world;
	Model* pModel;

	int GetVertexIndex(int sideLength, int i, int j) const;
};

#endif