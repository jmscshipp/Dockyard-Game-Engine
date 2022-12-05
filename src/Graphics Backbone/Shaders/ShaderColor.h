#ifndef _ShaderColor
#define _ShaderColor

#include "Shader.h"

struct ID3D11Buffer;

class ShaderColor : public Shader
{
public:
	ShaderColor();
	ShaderColor(const ShaderColor&) = delete;				 // Copy constructor
	ShaderColor(ShaderColor&&) = default;                    // Move constructor
	ShaderColor& operator=(const ShaderColor&) & = default;  // Copy assignment operator
	ShaderColor& operator=(ShaderColor&&) & = default;       // Move assignment operator
	~ShaderColor();		  							         // Destructor

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldColor(const Matrix& world, const Vect& col);

private:
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*           mpBufferCamMatrices;

	struct Data_WorldColor
	{
		Matrix World;
		Vect Color;
	};

	ID3D11Buffer*           mpBuffWordColor;
};

#endif _ShaderColor
