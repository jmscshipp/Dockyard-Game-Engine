#include "Terrain.h"
#include "Model.h"
#include "GraphicsObject_TextureOutlined.h"
#include "DirectXTex.h"
#include <assert.h>
#include "CollisionVolumeAABB.h"
#include "ColorLibrary.h"
#include "Collidable.h"
#include "CollisionVolumeBSphere.h"
#include <cmath>
#include "CollisionVisualizer.h"
#include "TextureManager.h"

Terrain::Terrain(LPCWSTR heightmapFile, std::string textureName, float vertexNum, float _cellSize, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	
	cellSize = _cellSize;

	int vertNum = vertexNum * vertexNum;
	StandardVertex* verts = new StandardVertex[vertNum];

	int triNum = (vertexNum - 1) * (vertexNum - 1) * 2;
	TriangleByIndex* tris = new TriangleByIndex[triNum];

	float urep = RepeatU / (vertexNum - 1);
	float vrep = RepeatV / (vertexNum - 1);

	float scale = (vertexNum / side);
	float yScale = (255 / maxheight);

	// setting up vertices
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			int texelIndex = GetTexelIndex(pixel_width, side, i / scale, j / scale);
			float x = (i - vertexNum / 2) * _cellSize;
			float y = hgtmap->pixels[texelIndex] / yScale + ytrans;
			float z = (j - vertexNum / 2) * _cellSize;
			verts[GetVertexIndex(vertexNum, i, j)].set(x, y, z, urep * i, vrep * j);
			//verts[GetVertexIndex(vertexNum, i, j)].set(i - vertexNum / 2, hgtmap->pixels[GetTexelIndex(pixel_width, side, i / scale, j / scale)] / yScale, j - vertexNum / 2, urep * i, vrep * j);
			//Trace::out("created vertex at %f, %f\n", i - len / 2, j - len / 2);
			// x : i
			// y : hgtmap->pixels[GetTexelIndex(pixel_width, side, i / scale, j / scale)] / yScale
			// z : j
			// u : urep * i
			// v : vrep * j
		}
	}

	cellOrigin = verts[GetVertexIndex(vertexNum, 0, 0)].Pos;

	// computing normals
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			// check to make sure we skip edge vertices
			if (i != 0 && i != vertexNum - 1 && j != 0 && j != vertexNum - 1)
			{
				// center
				StandardVertex* center = &verts[GetVertexIndex(vertexNum, i, j)];
				// left
				StandardVertex* left = &verts[GetVertexIndex(vertexNum, i - 1, j)];
				// right
				StandardVertex* right = &verts[GetVertexIndex(vertexNum, i + 1, j)];
				// up
				StandardVertex* up = &verts[GetVertexIndex(vertexNum, i, j + 1)];
				// down
				StandardVertex* down = &verts[GetVertexIndex(vertexNum, i, j - 1)];
				// down diagonal
				StandardVertex* downDiag = &verts[GetVertexIndex(vertexNum, i - 1, j - 1)];
				// up diagonal
				StandardVertex* upDiag = &verts[GetVertexIndex(vertexNum, i + 1, j + 1)];

				// left side face
				Vect edge1 = left->Pos - center->Pos;
				Vect helperEdge = up->Pos - center->Pos;
				edge1 = edge1.cross(helperEdge).getNorm();
				// right side face
				Vect edge2 = right->Pos - center->Pos;
				helperEdge = down->Pos - center->Pos;
				edge2 = edge2.cross(helperEdge).getNorm();
				// bottom left corner face
				Vect edge3 = left->Pos - center->Pos;
				helperEdge = downDiag->Pos - center->Pos;
				edge3 = edge3.cross(helperEdge).getNorm();
				// bottom right corner face
				Vect edge4 = down->Pos - center->Pos;
				helperEdge = downDiag->Pos - center->Pos;
				edge4 = edge4.cross(helperEdge).getNorm();
				// top left corner face
				Vect edge5 = up->Pos - center->Pos;
				helperEdge = upDiag->Pos - center->Pos;
				edge5 = edge5.cross(helperEdge).getNorm();
				// top right corner face
				Vect edge6 = right->Pos - center->Pos;
				helperEdge = upDiag->Pos - center->Pos;
				edge6 = edge6.cross(helperEdge).getNorm();

				helperEdge = Vect((edge1.X() + edge2.X() + edge3.X() + edge4.X() + edge5.X() + edge6.X()) / 6,
					(edge1.Y() + edge2.Y() + edge3.Y() + edge4.Y() + edge5.Y() + edge6.Y()) / 6,
					(edge1.Z() + edge2.Z() + edge3.Z() + edge4.Z() + edge5.Z() + edge6.Z()) / 6);

				verts[GetVertexIndex(vertexNum, i, j)].normal = helperEdge;

			}
			else
				verts[GetVertexIndex(vertexNum, i, j)].normal = Vect(0, 0, 0);
		}
	}

	cellsPerSide = vertexNum - 1;
	int cellNum = (vertexNum - 1) * (vertexNum - 1);
	cellAABBs = new CollisionVolumeAABB[cellNum];
	int AABBcounter = 0;

	// setting up triangles and aabb array
	int triangleIndex = 0;
	for (int i = 0; i < vertexNum - 1; i++)
	{
		for (int j = 0; j < vertexNum - 1; j++)
		{
			// indices for tri / aabb corners
			int corner0 = j + (vertexNum * i) + 1;
			int corner1 = j + vertexNum + (vertexNum * i);
			int corner2 = j + (vertexNum * i);
			int corner3 = j + vertexNum + (vertexNum * i) + 1;

			// setting tris
			tris[triangleIndex++].set(corner0, corner1, corner2);
			tris[triangleIndex++].set(corner0, corner3, corner1);

			// finding min and max for aabb
			Vect min = verts[corner0].Pos;
			Vect max = verts[corner0].Pos;
			
			// corner 1
			if (verts[corner1].Pos.X() < min.X()) // x
				min.X() = verts[corner1].Pos.X();
			if (verts[corner1].Pos.X() > max.X())
				max.X() = verts[corner1].Pos.X();
			if (verts[corner1].Pos.Y() < min.Y()) // y
				min.Y() = verts[corner1].Pos.Y();
			if (verts[corner1].Pos.Y() > max.Y())
				max.Y() = verts[corner1].Pos.Y();
			if (verts[corner1].Pos.Z() < min.Z()) // z
				min.Z() = verts[corner1].Pos.Z();
			if (verts[corner1].Pos.Z() > max.Z())
				max.Z() = verts[corner1].Pos.Z();
			// corner 2
			if (verts[corner2].Pos.X() < min.X()) // x
				min.X() = verts[corner2].Pos.X();
			if (verts[corner2].Pos.X() > max.X())
				max.X() = verts[corner2].Pos.X();
			if (verts[corner2].Pos.Y() < min.Y()) // y
				min.Y() = verts[corner2].Pos.Y();
			if (verts[corner2].Pos.Y() > max.Y())
				max.Y() = verts[corner2].Pos.Y();
			if (verts[corner2].Pos.Z() < min.Z()) // z
				min.Z() = verts[corner2].Pos.Z();
			if (verts[corner2].Pos.Z() > max.Z())
				max.Z() = verts[corner2].Pos.Z();
			// corner 3
			if (verts[corner3].Pos.X() < min.X()) // x
				min.X() = verts[corner3].Pos.X();
			if (verts[corner3].Pos.X() > max.X())
				max.X() = verts[corner3].Pos.X();
			if (verts[corner3].Pos.Y() < min.Y()) // y
				min.Y() = verts[corner3].Pos.Y();
			if (verts[corner3].Pos.Y() > max.Y())
				max.Y() = verts[corner3].Pos.Y();
			if (verts[corner3].Pos.Z() < min.Z()) // z
				min.Z() = verts[corner3].Pos.Z();
			if (verts[corner3].Pos.Z() > max.Z())
				max.Z() = verts[corner3].Pos.Z();
			
			cellAABBs[AABBcounter].ComputeData(min, max);
			AABBcounter++;
		}
	}

	pModTerrain = new Model(verts, vertNum, tris, triNum);
	gObjOutlined = new GraphicsObject_TextureOutlined(pModTerrain, TextureManager::GetTexture(textureName), Colors::Black, 5.0f);

	delete[] verts;
	delete[] tris;
}

int Terrain::GetVertexIndex(int sideLength, int i, int j) const
{
	return i * sideLength + j;
}

int Terrain::GetTexelIndex(size_t pixelWidth, int sideLength, int i, int j) const
{
	return pixelWidth * (j * sideLength + i);
}

void Terrain::Render() const
{
	gObjOutlined->RenderSolid();
}

void Terrain::Intersect(Collidable* col) const 
{
	col->GetCollisionVolume().DebugView(Colors::Pink);
	col->GetDefaultBSphere().DebugView(Colors::Purple);

	Vect max = col->GetDefaultBSphere().GetMax();
	Vect min = col->GetDefaultBSphere().GetMin();

	int minX = std::floor((min.X() - cellOrigin.X()) / cellSize);
	int minZ = std::floor((min.Z() - cellOrigin.Z()) / cellSize);

	// correct x in case outside of terrain boundaries
	if (minX < 0)
		minX = 0;
	else if (minX > cellsPerSide)
		minX = cellsPerSide;
	// correct z in case outside of terrain boundaries
	if (minZ < 0)
		minZ = 0;
	else if (minZ > cellsPerSide)
		minZ = cellsPerSide;

	int maxX = std::ceil((max.X() - cellOrigin.X()) / cellSize);
	int maxZ = std::ceil((max.Z() - cellOrigin.Z()) / cellSize);

	// correct x in case outside of terrain boundaries
	if (maxX < 0)
		maxX = 0;
	else if (maxX > cellsPerSide)
		maxX = cellsPerSide;
	// correct z in case outside of terrain boundaries
	if (maxZ < 0)
		maxZ = 0;
	else if (maxZ > cellsPerSide)
		maxZ = cellsPerSide;

	for (int i = minX; i < maxX; i++)
	{
		for (int j = minZ; j < maxZ; j++)
		{
			CollisionVolumeAABB* cell = GetCellAtIndices(i, j);
			if (cell->IntersectAccept(col->GetDefaultBSphere()))
			{
				if (cell->IntersectAccept(col->GetCollisionVolume()))
				{
					col->CollisionTerrain();
					cell->DebugView(Colors::Black);
				}
				else
					cell->DebugView(Colors::Yellow);
				continue;
			}
			else
				cell->DebugView(Colors::Red);
		}
	}
}

Model* Terrain::GetModel() const
{
	return pModTerrain;
}

CollisionVolumeAABB* Terrain::GetCellAtIndices(int xIndex, int zIndex) const
{
	return &cellAABBs[xIndex * cellsPerSide + zIndex];
}

CollisionVolumeAABB* Terrain::GetCellAtPosition(const Vect& pos) const
{
	int x = (pos.X() - cellOrigin.X()) / cellSize;
	int z = (pos.Z() - cellOrigin.Z()) / cellSize;

	// correct x in case outside of terrain boundaries
	if (x < 0)
		x = 0;
	else if (x > cellsPerSide - 1)
		x = cellsPerSide - 1;
	// correct z in case outside of terrain boundaries
	if (z < 0)
		z = 0;
	else if (z > cellsPerSide - 1)
		z = cellsPerSide - 1;

	return GetCellAtIndices(x, z);
}

void Terrain::UpdateInfoAtPoint(const Vect& pos)
{
	int x = (pos.X() - cellOrigin.X()) / cellSize;
	int z = (pos.Z() - cellOrigin.Z()) / cellSize;

	// correct x in case outside of terrain boundaries
	if (x < 0)
		x = 0;
	else if (x > cellsPerSide - 1)
		x = cellsPerSide - 1;
	// correct z in case outside of terrain boundaries
	if (z < 0)
		z = 0;
	else if (z > cellsPerSide - 1)
		z = cellsPerSide - 1;

	int verticesPerSide = cellsPerSide + 1;

	// vertices of cell corners
	StandardVertex* topRightCorner = &pModTerrain->GetVertexArray()[z + (verticesPerSide * x) + 1];					
	StandardVertex* bottomLeftCorner = &pModTerrain->GetVertexArray()[z + verticesPerSide + (verticesPerSide * x)];	
	StandardVertex* bottomRightCorner = &pModTerrain->GetVertexArray()[z + (verticesPerSide * x)];					
	StandardVertex* topLeftCorner = &pModTerrain->GetVertexArray()[z + verticesPerSide + (verticesPerSide * x) + 1];

	Vect divider = pos - bottomLeftCorner->Pos;
	StandardVertex *pointA, *pointB, *pointC;

	// if in upper triangle
	if (-divider.Z() < divider.X())
	{
		pointA = bottomLeftCorner;
		pointB = topLeftCorner;
		pointC = topRightCorner;
		//CollisionVisualizer::ShowBoxAtPos(pointB->Pos.X(), pointB->Pos.Y(), pointB->Pos.Z(), Colors::Pink);
	}
	else // lower triangle
	{
		pointA = bottomLeftCorner;
		pointB = bottomRightCorner;
		pointC = topRightCorner;
		//CollisionVisualizer::ShowBoxAtPos(pointB->Pos.X(), pointB->Pos.Y(), pointB->Pos.Z(), Colors::Blue);
	}

	//CollisionVisualizer::ShowBoxAtPos(pointA->Pos.X(), pointA->Pos.Y(), pointA->Pos.Z(), Colors::Red);

	//CollisionVisualizer::ShowBoxAtPos(pointC->Pos.X(), pointC->Pos.Y(), pointC->Pos.Z(), Colors::LimeGreen);

	//  --- barycentric calculations ---

	Vect pointAFlat(pointA->Pos.X(), 0, pointA->Pos.Z());
	Vect pointBFlat(pointB->Pos.X(), 0, pointB->Pos.Z());
	Vect pointCFlat(pointC->Pos.X(), 0, pointC->Pos.Z());
	Vect posFlat(pos.X(), 0, pos.Z());

	Vect v0 = pointBFlat - pointAFlat;
	Vect v1 = pointCFlat - pointBFlat;
	Vect v2 = posFlat - pointAFlat;
	
	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);
	
	float beta = (d * c - b * e) / (a * c - b * b);
	float gamma = (a * e - d * b) / (a * c - b * b);

	float yVal = pointA->Pos.Y() + beta * (pointB->Pos.Y() - pointA->Pos.Y()) + gamma * (pointC->Pos.Y() - pointB->Pos.Y());

	// calculate exact point on terrain
	positionAtPoint = Vect(pos.X(), yVal, pos.Z());

	//CollisionVisualizer::ShowBoxAtPos(positionAtPoint.X(), positionAtPoint.Y(), positionAtPoint.Z(), Colors::PaleTurquoise);

	// calculate normal
	normalAtPoint = pointA->normal + beta * (pointB->normal - pointA->normal) + gamma * (pointC->normal - pointB->normal);

	//CollisionVisualizer::ShowLine(positionAtPoint, normalAtPoint, Colors::White);
}
Vect& Terrain::GetPositionAtPoint(const Vect& point)
{
	UpdateInfoAtPoint(point);
	return positionAtPoint;
}

Vect& Terrain::GetNormalAtPoint(const Vect& point)
{
	UpdateInfoAtPoint(point);
	return normalAtPoint;
}

Terrain::~Terrain()
{
	delete gObjOutlined;
	delete pModTerrain;
	delete[] cellAABBs;
}