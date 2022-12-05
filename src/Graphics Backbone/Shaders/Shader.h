#ifndef _Shader
#define _Shader

#include <d3dcommon.h>
#include "Matrix.h"
#include "GraphicsUtility.h"
#include <string>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11InputLayout;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct D3D11_INPUT_ELEMENT_DESC;

class Shader : public Align16
{
private:
	// Store these pointers to avoid passing them in every method
	ID3D11Device*			mDevice;
	ID3D11DeviceContext*	mContext;

	// Actual objects managed by this class
	ID3D11VertexShader*     mpVertexShader;
	ID3D11PixelShader*      mpPixelShader;
	ID3D11InputLayout*      mpVertexLayout;

	// Needed for building shaders
	ID3DBlob*				pVSBlob;
	ID3DBlob*				pPSBlob;

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	void privBuildShaders(WCHAR* filename, LPCSTR vsModel, LPCSTR psModel);

protected:
	ID3D11Device* GetDevice(); 
	
	Shader(WCHAR* filename, LPCSTR vsModel = "vs_4_0", LPCSTR psModel = "ps_4_0");
	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layoutdesc, UINT size);
	void SetContext(ID3D11DeviceContext* devcon);
	void SetToContext_VS_PS_InputLayout();

public:
	Shader(const Shader&) = delete;				  // Copy constructor
	Shader(Shader&&) = delete;                    // Move constructor
	Shader& operator=(const Shader&) & = delete;  // Copy assignment operator
	Shader& operator=(Shader&&) & = delete;       // Move assignment operator
	Shader() = delete;
	virtual ~Shader();

	virtual void SetToContext(ID3D11DeviceContext* devcon) {};
	ID3D11DeviceContext* GetContext();
};

#endif _Shader