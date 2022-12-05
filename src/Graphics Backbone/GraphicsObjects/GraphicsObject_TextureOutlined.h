#ifndef _GraphicsObject_TextureOutlined
#define _GraphicsObject_TextureOutlined

#include "GraphicsObject_Base.h"
#include "ColorLibrary.h"

// forward declarations
class ShaderTexture;
class ShaderOutline;
class Texture;

class GraphicsObject_TextureOutlined : public GraphicsObject_Base
{
public:
	GraphicsObject_TextureOutlined(Model* model, Texture* tex = nullptr, const Vect& colorForOutline = Colors::Black, float sizeForOutline = 1.0f);
	GraphicsObject_TextureOutlined(const GraphicsObject_TextureOutlined&) = delete;				 // Copy constructor
	GraphicsObject_TextureOutlined(GraphicsObject_TextureOutlined&&) = default;                  // Move constructor
	GraphicsObject_TextureOutlined& operator=(const GraphicsObject_TextureOutlined&) = default;  // Copy assignment operator
	GraphicsObject_TextureOutlined& operator=(GraphicsObject_TextureOutlined&&) = default;       // Move assignment operator
	~GraphicsObject_TextureOutlined();		  												 // Destructor

	// sets for all meshes
	void SetTexture(Texture* tex);
	// sets for specific mesh
	void SetTexture(Texture* tex, int meshIndex);
	void SetOutlineColor(const Vect& newColor);
	void SetOutlineSize(float newSize);
	void SetWorld(const Matrix& worldMat);

	virtual void RenderSolid() override;
	virtual void RenderWireframe() override;

protected:
	// flat textured render
	ShaderTexture* pObjectShader;
	int meshCount;
	Texture** textures;

	// flat color outline
	ShaderOutline* pOutlineShader;
	Vect outlineColor;
	float outlineSize;

	Matrix world;
};

#endif