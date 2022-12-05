#include <assert.h>
#include "File.h"
#include "Model.h"
#include "ModelTools.h"
#include "AzulFileHdr.h"
#include "MeshSeparator.h"
#include "GPUController.h"
#include "GraphicsUtility.h"

Model::Model(StandardVertex* vertList, int nverts, TriangleByIndex* triList, int ntri)
{
	assert(nverts > 0);
	assert(ntri > 0);

	mDevice = GPUController::GetDevice();

	// Copy Data
	numVerts = nverts;
	pVerts = new StandardVertex[numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		pVerts[i] = vertList[i];
	}
	numTris = ntri;
	pTris = new TriangleByIndex[numTris];
	for (int i = 0; i < numTris; i++)
	{
		pTris[i] = triList[i];
	}

	privLoadDataToGPU();
	CalculateModelInfo();
}

Model::Model(const char* const _modelName)
{
	mDevice = GPUController::GetDevice();
	pVerts = nullptr;
	pTris = nullptr;
	numVerts = 0;
	numTris = 0;

	privLoadDataFromFile(_modelName, pVerts, numVerts, pTris, numTris);
	privLoadDataToGPU();
	CalculateModelInfo();
}

Model::Model(Model::PreMadeModels pm)
{
	mDevice = GPUController::GetDevice();
	pVerts = nullptr;
	pTris = nullptr;
	numVerts = 0;
	numTris = 0;

	switch (pm)
	{
	case UnitSquare2D:
		ModelTools::Create2dUnitBox(pVerts, numVerts, pTris, numTris);
		break;
	case UnitBox:
		ModelTools::CreateUnitBox(pVerts, numVerts, pTris, numTris);
		break;
	case UnitBoxRepeatedTexture:
		ModelTools::CreateUnitBoxRepTexture(pVerts, numVerts, pTris, numTris);
		break;
	case UnitPyramid:
		ModelTools::CreateUnitPyramid(pVerts, numVerts, pTris, numTris);
		break;
	case UnitPyramidRepeatedTexture:
		ModelTools::CreateUnitPyramidRepTexture(pVerts, numVerts, pTris, numTris);
		break;
	case UnitSphere:
		ModelTools::CreateUnitSphere(12, 12, pVerts, numVerts, pTris, numTris);
		break;
	default:
		assert(false && "Invalid option");
	}

	privLoadDataToGPU();
	CalculateModelInfo();
}

Model::~Model()
{
	delete[] pTris;
	delete[] pVerts;

	delete meshes;

	ReleaseAndDeleteCOMobject(mpVertexBuffer);
	ReleaseAndDeleteCOMobject(mpIndexBuffer);
}

// vertices info
StandardVertex* Model::GetVertexArray()
{
	return pVerts;
}

int Model::GetVertexNum()
{
	return numVerts;
}

// tris info
TriangleByIndex* Model::GetTriArray()
{
	return pTris;
}

int Model::GetTriNum()
{
	return numTris;
}

void Model::privLoadDataFromFile(const char* const _modelName, StandardVertex*& verts, int& nverts, TriangleByIndex*& tris, int& ntri)
{
	// Read from file
	FileHandle fh;
	FileError  ferror;

	ferror = File::open(fh, _modelName, FILE_READ);
	assert(ferror == FILE_SUCCESS);

	// Get the file format for the data
	AzulFileHdr  azulFileHdr;

	// **** Overly complicated detour Part 1:  The vertex data in the file is packed efficiently
	// whereas our StandardVertex is not. Something I shall fix form the start next time.
	// For time time: we will read in the data into a temp array and then manually copy the data into
	// the StandardVertex array. 

	struct VertexStride_VUN
	{
		float x;    // Vert - V
		float y;
		float z;

		float u;    // UV tex coor - U
		float v;

		float txt;	// texture trickery 

		float nx;   // Norm verts - N
		float ny;
		float nz;

		float r;
		float g;
		float b;

		void set(float _x, float _y, float _z,
			float _u, float _v,
			float _nx, float _ny, float _nz,
			float _txt = 0,
			float _r = 1, float _g = 1, float _b = 1)
		{
			x = _x;
			y = _y;
			z = _z;
			u = _u;
			v = _v;
			nx = _nx;
			ny = _ny;
			nz = _nz;

			txt = _txt;
			r = _r;
			g = _g;
			b = _b;
		}

	};

	// Read the header
	ferror = File::read(fh, &azulFileHdr, sizeof(AzulFileHdr));
	assert(ferror == FILE_SUCCESS);

	// create the vertex buffer
	nverts = azulFileHdr.numVerts;
	VertexStride_VUN* pTmpVerts = new VertexStride_VUN[nverts];

	// load the verts
	// seek to the location
	ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.vertBufferOffset);
	assert(ferror == FILE_SUCCESS);

	// read it
	ferror = File::read(fh, pTmpVerts, nverts * sizeof(VertexStride_VUN));
	assert(ferror == FILE_SUCCESS);

	// create the triLists buffer
	ntri = azulFileHdr.numTriangles;
	tris = new TriangleByIndex[ntri];

	// load the triList
	// seek to the location
	ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.triangleListBufferOffset);
	assert(ferror == FILE_SUCCESS);

	// read it
	ferror = File::read(fh, tris, ntri * sizeof(TriangleByIndex));
	assert(ferror == FILE_SUCCESS);

	// close
	ferror = File::close(fh);
	assert(ferror == FILE_SUCCESS);

	// **** Overly complicated detour Part 2: now we copy the vertex data into our StandardVertex
	verts = new StandardVertex[nverts];
	StandardVertex* v;
	VertexStride_VUN* tmp;
	for (int i = 0; i < nverts; i++)
	{
		tmp = &(pTmpVerts[i]);
		v = &(verts[i]);
		v->set(tmp->x, tmp->y, tmp->z, tmp->u, tmp->v, tmp->nx, tmp->ny, tmp->nz, tmp->r, tmp->g, tmp->b, (int)tmp->txt);
	}

	delete[] pTmpVerts;
}

void  Model::privLoadDataToGPU()
{
	// Extract mesh information
	meshes = new MeshSeparator(pVerts, numVerts, pTris, numTris);

	// Vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StandardVertex) * numVerts;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pVerts;
	HRESULT hr = mDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);
	assert(SUCCEEDED(hr));

	// Index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TriangleByIndex) * numTris;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = pTris;
	hr = mDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);
	assert(SUCCEEDED(hr));
}

bool Model::ValidMeshNum(int meshnum)
{
	return (meshnum >= 0) && (meshnum < GetMeshCount());
}

int Model::GetMeshCount()
{
	return meshes->GetMeshCount();
}

void Model::SetToContext(ID3D11DeviceContext* context)
{
	UINT stride = sizeof(StandardVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::Render(ID3D11DeviceContext* context)
{
	context->DrawIndexed(numTris * 3, 0, 0);
}

void Model::RenderMesh(ID3D11DeviceContext* context, int meshnum)
{
	assert(ValidMeshNum(meshnum));

	int tricount, trioffset;
	meshes->GetMeshTriCountAndOffset(meshnum, tricount, trioffset);

	context->DrawIndexed(tricount * 3, trioffset * 3, 0);
}

void Model::CalculateModelInfo()
{
	minAABB = maxAABB = pVerts[0].Pos;

	Vect temp;
	for (int i = 0; i < numVerts; i++) // setting minAABB and maxAABB
	{
		temp = pVerts[i].Pos;
		if (temp.X() < minAABB.X())
			minAABB.X() = temp.X();
		else if (temp.X() > maxAABB.X())
			maxAABB.X() = temp.X();

		if (temp.Y() < minAABB.Y())
			minAABB.Y() = temp.Y();
		else if (temp.Y() > maxAABB.Y())
			maxAABB.Y() = temp.Y();

		if (temp.Z() < minAABB.Z())
			minAABB.Z() = temp.Z();
		else if (temp.Z() > maxAABB.Z())
			maxAABB.Z() = temp.Z();
	}
	center = minAABB + (0.5f * (maxAABB - minAABB)); // setting center

	temp.X() = (abs(minAABB.X()) > abs(maxAABB.X())) ? abs(minAABB.X()) : abs(maxAABB.X());
	temp.Y() = (abs(minAABB.Y()) > abs(maxAABB.Y())) ? abs(minAABB.Y()) : abs(maxAABB.Y());
	temp.Z() = (abs(minAABB.Z()) > abs(maxAABB.Z())) ? abs(minAABB.Z()) : abs(maxAABB.Z());
	radius = temp.mag(); // setting radius
}

const Vect& Model::GetCenter()
{
	return center;
}

float Model::GetRadius()
{
	return radius;
}

const Vect& Model::GetMinAABB()
{
	return minAABB;
}

const Vect& Model::GetMaxAABB()
{
	return maxAABB;
}