#ifndef _GraphicsObject_Base
#define _GraphicsObject_Base

#include "Matrix.h"

class Model;
class ShaderMeshData;
struct ID3D11DeviceContext;
class Shader;

class GraphicsObject_Base : public Align16
{
public:
	GraphicsObject_Base(const GraphicsObject_Base&) = delete;				   // Copy constructor
	GraphicsObject_Base(GraphicsObject_Base&&) = default;                    // Move constructor
	GraphicsObject_Base& operator=(const GraphicsObject_Base&) & = default;  // Copy assignment operator
	GraphicsObject_Base& operator=(GraphicsObject_Base&&) & = default;       // Move assignment operator
	~GraphicsObject_Base() = default;		  							   // Destructor
	GraphicsObject_Base();

	void SetModel(Model* mod);
	Model* GetModel();
	virtual void RenderSolid() = 0;
	virtual void RenderWireframe() = 0;

protected:
	Model* pModel;
};

#endif _GraphicsObject_Base
