#ifndef _ShaderOutline
#define _ShaderOutline

#include "Shader.h"

struct ID3D11Buffer;

class ShaderOutline : public Shader
{
public:
	ShaderOutline();
	ShaderOutline(const ShaderOutline&) = delete;				 // Copy constructor
	ShaderOutline(ShaderOutline&&) = default;                    // Move constructor
	ShaderOutline& operator=(const ShaderOutline&) = default;  // Copy assignment operator
	ShaderOutline& operator=(ShaderOutline&&) = default;       // Move assignment operator
	~ShaderOutline();		  							         // Destructor

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

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
