#ifndef _GPUController
#define _GPUController

#include <d3d11.h>
#include "Vect.h"

class GPUController : public Align16
{
private:
	static GPUController* instance; // set up as singleton

	GPUController();
	GPUController(const GPUController&) = delete;
	GPUController(GPUController&&) = default;
	GPUController& operator=(const GPUController&) = default;
	GPUController& operator=(GPUController&&) = default;
	~GPUController();

	static GPUController& Instance()
	{
		if (!instance)
			instance = new GPUController();
		return *instance;
	};

	// DX application elements
	ID3D11Device* md3dDevice;					      // Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	      // Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					      // image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	      // Where to send rendering operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView;       // Needed to force depth-buffer operations
	ID3D11RasterizerState* mRasterizerSolid;	      // different rasterizer states ->
	ID3D11RasterizerState* mRasterizerWireframe;      // for rendering graphicsobjects in different modes
	ID3D11RasterizerState* mRasterizerFrontcullSolid; // this one for outline shader / gObject
	ID3D11BlendState* mBlendState;				      // for enabling alpha blending (transparency)

	Vect BackgroundColor;

	// Debug utility
	void ReportLiveDXObjects();
	// set up DX 11
	void PrivInitDirect3D(const HWND& window, int windowWidth, int windowHeight);
	// changes background color
	void PrivSetBackgroundColor(const Vect& newColor); 
	// clears render target and depth stencil views
	void PrivResetContext();
	// Switches the display to show the now-finished back-buffer
	void PrivSwapChainSwitch();
	void PrivSetRasterizerSolid();
	void PrivSetRasterizerWireframe();
	void PrivSetRasterizerFrontcullSolid();

public:
	static void InitDirect3D(const HWND& window, int windowWidth, int windowHeight) { Instance().PrivInitDirect3D(window, windowWidth, windowHeight); };
	static ID3D11Device* GetDevice() { return Instance().md3dDevice; };
	static ID3D11DeviceContext* GetContext() { return Instance().md3dImmediateContext; };
	static void SetBackgroundColor(const Vect& newColor) { Instance().PrivSetBackgroundColor(newColor); }
	static void ResetContext() { Instance().PrivResetContext(); };
	static void SwapChainSwitch() { Instance().PrivSwapChainSwitch(); };
	static void SetRasterizerSolid() { Instance().PrivSetRasterizerSolid(); };
	static void SetRasterizerWireframe() { Instance().PrivSetRasterizerWireframe(); };
	static void SetRasterizerFrontcullSolid() { Instance().PrivSetRasterizerFrontcullSolid(); };
	static void Delete() { delete Instance().instance; };
};

#endif _GPUController