#ifndef MODEL_H
#define MODEL_H

#include <d3d11.h>
#include "Matrix.h"

// forward declaration
class MeshSeparator;

struct StandardVertex : public Align16
{
	Vect Pos;
	float u;
	float v;
	Vect normal;
	Vect Color;
	int meshNum;		// new property

	void set(float _x, float _y, float _z,
		float _u = 0, float _v = 0,
		float _nx = 0, float _ny = 0, float _nz = 0,
		float _r = 1, float _g = 1, float _b = 1, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		normal = Vect(_nx, _ny, _nz, 0);
		Color = Vect(_r, _g, _b);
		meshNum = num;
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vect& n, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		normal = n;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = 0;
		v = 0;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, const Vect& n, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = 0;
		v = 0;
		normal = n;
		Color = c;
		meshNum = num;
	}

	void set(const Vect& p, const Vect& c)
	{
		Pos = p;
		Color = c;
	}
};

struct TriangleByIndex
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;

	void set(int _v0, int _v1, int _v2)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
	}
};

class Model
{
public:
	enum PreMadeModels
	{
		UnitSquare2D,
		UnitBox,
		UnitBoxRepeatedTexture,
		UnitPyramid,
		UnitPyramidRepeatedTexture,
		UnitBoxSixFacesTexture,
		UnitSphere
	};

	// big six
	Model() = delete;
	Model(StandardVertex* pVerts, int nverts, TriangleByIndex* ptlist, int ntri);
	Model(PreMadeModels pm);
	Model(const char* const _modelName);
	Model(const Model&) = delete;			  // Copy constructor
	Model(Model&&) = delete;                  // Move constructor
	Model& operator=(const Model&) = delete;  // Copy assignment operator
	Model& operator=(Model&&) = delete;       // Move assignment operator
	virtual ~Model();

	void SetToContext(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context);
	void RenderMesh(ID3D11DeviceContext* context, int meshnum);

	// access mesh info
	int GetMeshCount();
	bool ValidMeshNum(int i);
	// vertices info
	StandardVertex* GetVertexArray();
	int GetVertexNum();
	// tris info
	TriangleByIndex* GetTriArray();
	int GetTriNum();
	// info for collision volumes
	const Vect& GetCenter();
	float GetRadius();
	const Vect& GetMinAABB();
	const Vect& GetMaxAABB();

private:
	// model info
	Vect center, minAABB, maxAABB;
	StandardVertex* pVerts;
	TriangleByIndex* pTris;
	MeshSeparator* meshes;
	// GPU connections
	ID3D11Device* mDevice;
	ID3D11Buffer* mpVertexBuffer;
	ID3D11Buffer* mpIndexBuffer;
	int numVerts;
	int numTris;
	float radius;

	void CalculateModelInfo();
	void privLoadDataToGPU();
	void privLoadDataFromFile(const char* const _modelName, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& ptlist, int& ntri);
};

#endif