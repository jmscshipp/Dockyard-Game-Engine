#ifndef _WindowController
#define _WindowController

#include "InputUtility.h"

class WindowController : public Align16
{
private:
	static WindowController* instance; // set up as singleton

	WindowController();
	WindowController(const WindowController&) = delete;
	WindowController(WindowController&&) = default;
	WindowController& operator=(const WindowController&) = default;
	WindowController& operator=(WindowController&&) = default;
	~WindowController();

	static WindowController& Instance()
	{
		if (!instance)
			instance = new WindowController();
		return *instance;
	};

	int NonstaticRunProgram(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow);
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	void PrivSetWindowWidthHeight(int w, int h);
	void PrivSetWindowName(const char* name);
	bool PrivIsKeyPressed(const KEY k);

	HINSTANCE g_hInst;
	int cmdShow;
	HWND g_hWnd;
	int windowWidth, windowHeight;

public:
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static int WINAPI RunProgram(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
	{ return Instance().NonstaticRunProgram(hInstance, hPrevInstance, lpCmdLine, nCmdShow); }
	static void Delete() { delete Instance().instance; };

	static int GetWindowWidth() { return Instance().windowWidth; };
	static int GetWindowHeight() { return Instance().windowHeight; };
	static void SetWindowWidthHeight(int w, int h) { Instance().PrivSetWindowWidthHeight(w, h); };
	static void SetWindowName(const char* name) { Instance().PrivSetWindowName(name); };
	static bool IsKeyPressed(const KEY k) { return Instance().PrivIsKeyPressed(k); };
};

#endif _WindowController