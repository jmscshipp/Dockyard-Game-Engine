// FlatPlane.h
// Berthiaume Jan 2017

#ifndef _Skybox
#define _Skybox

#include "Matrix.h"

class Model;
struct ID3D11DeviceContext;

class Skybox : public Align16
{
private:
	Model* pPlane;

public:
	Skybox(const Skybox&) = delete;				// Copy constructor
	Skybox(Model&&) = delete;						// Move constructor
	Skybox& operator=(const Skybox&) = delete;  // Copy assignment operator
	Skybox& operator=(Skybox&&) = delete;       // Move assignment operator
	~Skybox();

	Skybox(float boxSize, float urep, float vrep);

	void Render(ID3D11DeviceContext* context);

};

#endif _Skybox
