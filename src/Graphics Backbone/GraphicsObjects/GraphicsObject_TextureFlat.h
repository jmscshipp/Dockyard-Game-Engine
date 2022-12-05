#ifndef _GraphicsObject_TextureFlat
#define _GraphicsObject_TextureFlat

#include "GraphicsObject_Base.h"

// forward declarations
class ShaderTexture;
class Texture;

class GraphicsObject_TextureFlat : public GraphicsObject_Base
{
public:
	GraphicsObject_TextureFlat(Model* model, Texture* tex = nullptr);
	GraphicsObject_TextureFlat(const GraphicsObject_TextureFlat&) = delete;				 // Copy constructor
	GraphicsObject_TextureFlat(GraphicsObject_TextureFlat&&) = default;                  // Move constructor
	GraphicsObject_TextureFlat& operator=(const GraphicsObject_TextureFlat&) = default;  // Copy assignment operator
	GraphicsObject_TextureFlat& operator=(GraphicsObject_TextureFlat&&) = default;       // Move assignment operator
	~GraphicsObject_TextureFlat();		  												 // Destructor

	// sets for all meshes
	void SetTexture(Texture* tex);
	// sets for specific mesh
	void SetTexture(Texture* tex, int meshIndex);
	void SetWorld(const Matrix& worldMat);

	virtual void RenderSolid() override;
	virtual void RenderWireframe() override;

protected:
	ShaderTexture* pShader;
	int meshCount;
	Texture** textures;
	Matrix world;
};

#endif