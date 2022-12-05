#ifndef _GraphicsObject_Sprite
#define _GraphicsObject_Sprite

#include "GraphicsObject_Base.h"

// forward declarations
class ShaderTexture;
class Texture;

class GraphicsObject_Sprite : public GraphicsObject_Base
{
public:
	GraphicsObject_Sprite(Texture* _tex = nullptr);
	GraphicsObject_Sprite(const GraphicsObject_Sprite&) = delete;				 // Copy constructor
	GraphicsObject_Sprite(GraphicsObject_Sprite&&) = default;                  // Move constructor
	GraphicsObject_Sprite& operator=(const GraphicsObject_Sprite&) = default;  // Copy assignment operator
	GraphicsObject_Sprite& operator=(GraphicsObject_Sprite&&) = default;       // Move assignment operator
	~GraphicsObject_Sprite();		  												 // Destructor

	void SetTexture(Texture* tex);
	void SetWorld(const Matrix& worldMat);
	void SetPosition(const Vect& pos);
	const Vect& GetPosition();
	virtual void RenderSolid() override;
	virtual void RenderWireframe() override;

protected:
	ShaderTexture* pShader;
	Texture* tex;
	Matrix world;
	Vect position;
};

#endif