#ifndef _GraphicsObject_ColorLight
#define _GraphicsObject_ColorLight

#include "GraphicsObject_Base.h"

// forward declaration
class ShaderColorLight;
class Model;

class GraphicsObject_ColorLight : public GraphicsObject_Base
{
public:
	GraphicsObject_ColorLight(Model* model);
	GraphicsObject_ColorLight(const GraphicsObject_ColorLight&) = delete;			   // Copy constructor
	GraphicsObject_ColorLight(GraphicsObject_ColorLight&&) = default;                  // Move constructor
	GraphicsObject_ColorLight& operator=(const GraphicsObject_ColorLight&) = default;  // Copy assignment operator
	GraphicsObject_ColorLight& operator=(GraphicsObject_ColorLight&&) = default;       // Move assignment operator
	~GraphicsObject_ColorLight();		  											   // Destructor

	// set for all materials
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	// set for specific material
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num);
	void SetWorld(const Matrix& worldMat);

	virtual void RenderSolid() override;
	virtual void RenderWireframe() override;

	friend class ShaderColorLight;

protected:

	struct Material
	{
		Vect ambient;
		Vect diffuse;
		Vect specular;
	};

	ShaderColorLight* pShader;
	Material* materials;
	Matrix world;
	int meshCount;
};

#endif