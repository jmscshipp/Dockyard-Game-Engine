#ifndef _GraphicsObject_ColorFlat
#define _GraphicsObject_ColorFlat

#include "GraphicsObject_Base.h"

// forward declartion
class ShaderColor;

class GraphicsObject_ColorFlat : public GraphicsObject_Base
{
friend class ShaderColor;

public:
	GraphicsObject_ColorFlat() = delete;
	GraphicsObject_ColorFlat(Model* mod, const Vect& color);
	GraphicsObject_ColorFlat(const GraphicsObject_ColorFlat&) = delete;				 // Copy constructor
	GraphicsObject_ColorFlat(GraphicsObject_ColorFlat&&) = default;                    // Move constructor
	GraphicsObject_ColorFlat& operator=(const GraphicsObject_ColorFlat&) & = default;  // Copy assignment operator
	GraphicsObject_ColorFlat& operator=(GraphicsObject_ColorFlat&&) & = default;       // Move assignment operator
	~GraphicsObject_ColorFlat();		  											 // Destructor

	void SetColor(const Vect& col);
	void SetColor(const Vect& col, int meshnum);
	void SetWorld(const Matrix& m);

	void RenderSolid() override;
	void RenderWireframe() override;

private:
	ShaderColor* pShader;
	Vect* meshColors;
	Matrix world;
};

#endif _GraphicsObject_ColorFlat
