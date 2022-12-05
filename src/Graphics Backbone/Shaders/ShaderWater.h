#ifndef _ShaderWater
#define _ShaderWater

#include "Shader.h"

struct ID3D11Buffer;

//forward declaration
class Texture;

class ShaderWater : public Shader
{
public:
	ShaderWater();
	ShaderWater(const ShaderWater&) = delete;				 // Copy constructor
	ShaderWater(ShaderWater&&) = default;                    // Move constructor
	ShaderWater& operator=(const ShaderWater&) = default;  // Copy assignment operator
	ShaderWater& operator=(ShaderWater&&) = default;       // Move assignment operator
	~ShaderWater();		  							         // Destructor

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldColorSize(const Matrix& world, const Vect& col, float size);

private:
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldColorSize
	{
		Matrix World;
		Vect Color;
		float OutlineSize;
	};

	ID3D11Buffer* mpBuffWorldColorSize;
};

#endif _ShaderColor
