#ifndef _GraphicsObject_Cartoon
#define _GraphicsObject_Cartoon

#include "GraphicsObject_Base.h"

// forward declaration
class ShaderCartoon;
class Texture;
class Model;

class GraphicsObject_Cartoon : public GraphicsObject_Base
{
public:
	GraphicsObject_Cartoon() = delete;
	GraphicsObject_Cartoon(Model* model, const Vect& color0, const Vect& color1, const Vect& color2, Texture* tex = nullptr);
	GraphicsObject_Cartoon(const GraphicsObject_Cartoon&) = delete;				// Copy constructor
	GraphicsObject_Cartoon(GraphicsObject_Cartoon&&) = default;                   // Move constructor
	GraphicsObject_Cartoon& operator=(const GraphicsObject_Cartoon&) = default;   // Copy assignment operator
	GraphicsObject_Cartoon& operator=(GraphicsObject_Cartoon&&) = default;        // Move assignment operator
	~GraphicsObject_Cartoon();		  													// Destructor

	// set for all meshes
	void SetTexture(Texture* tex);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	// sets for specific mesh
	void SetTexture(Texture* tex, int meshIndex);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int meshIndex);

	// setting shader properties
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetFogValues(const float& fogStart, const float& fogRange, const Vect& fogColor);
	void SetWorld(const Matrix& worldMat);

	virtual void RenderSolid() override;
	virtual void RenderWireframe() override;

protected:

	struct Material
	{
		Vect ambient;
		Vect diffuse;
		Vect specular;
	};

	ShaderCartoon* pShader;
	int meshCount;
	Texture** textures;
	Material* materials;
	Matrix world;
	Vect Color0;
	Vect Color1;
	Vect Color2;
};

#endif