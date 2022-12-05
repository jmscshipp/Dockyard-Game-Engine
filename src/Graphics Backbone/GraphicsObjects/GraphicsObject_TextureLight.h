#ifndef _GraphicsObject_TextureLight
#define _GraphicsObject_TextureLight

#include "GraphicsObject_Base.h"

// forward declaration
class ShaderTextureLight;
class Texture;
class Model;

class GraphicsObject_TextureLight : public GraphicsObject_Base
{
public:
	GraphicsObject_TextureLight() = delete;
	GraphicsObject_TextureLight(Model* model, Texture* tex = nullptr);
	GraphicsObject_TextureLight(const GraphicsObject_TextureLight&) = delete;				// Copy constructor
	GraphicsObject_TextureLight(GraphicsObject_TextureLight&&) = default;                   // Move constructor
	GraphicsObject_TextureLight& operator=(const GraphicsObject_TextureLight&) = default;   // Copy assignment operator
	GraphicsObject_TextureLight& operator=(GraphicsObject_TextureLight&&) = default;        // Move assignment operator
	~GraphicsObject_TextureLight();		  													// Destructor
	
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

	ShaderTextureLight* pShader;
	int meshCount;
	Texture** textures;
	Material* materials;
	Matrix world;
};

#endif