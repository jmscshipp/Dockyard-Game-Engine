#ifndef _FlatPlane
#define _FlatPlane

class Model;
struct ID3D11DeviceContext;

class FlatPlane 
{
private:
	Model* pPlane;

public:
	FlatPlane(const FlatPlane&) = delete;				// Copy constructor
	FlatPlane(Model&&) = delete;                    // Move constructor
	FlatPlane& operator=(const FlatPlane&) & = delete;  // Copy assignment operator
	FlatPlane& operator=(FlatPlane&&) & = delete;       // Move assignment operator
	~FlatPlane();

	FlatPlane(float size, float hrep, float vrep);
	Model* GetModel();
	void Render(ID3D11DeviceContext* context);

};

#endif _FlatPlane
