#ifndef _ShaderTexture
#define _ShaderTexture

#include "Shader.h"

//forward declaration
class Texture;
struct ID3D11Buffer;

class ShaderTexture : public Shader
{
public:
	ShaderTexture();
	ShaderTexture(const ShaderTexture&) = delete;			
	ShaderTexture(ShaderTexture&&) = default;                  
	ShaderTexture& operator=(const ShaderTexture&) = default;  
	ShaderTexture& operator=(ShaderTexture&&) = default;       
	~ShaderTexture();		  							       

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorld(const Matrix& world);

private:
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct WorldData
	{
		Matrix World;
		float TimeVal;
	};

	ID3D11Buffer* mpBuffWorld;
};

#endif