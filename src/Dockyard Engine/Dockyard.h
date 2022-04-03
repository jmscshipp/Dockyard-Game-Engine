#ifndef _Dockyard
#define _Dockyard

#include "AzulCore.h"

class Dockyard: private Engine
{
private:
	static Dockyard* instance; // set up as singleton

	// big four
	Dockyard() = default;
	Dockyard(const Dockyard&) = delete;
	Dockyard& operator = (const Dockyard&) = delete;
	~Dockyard() = default;

	// legacy
	//Dockyard( const char* windowName, const int Width,const int Height);

	static Dockyard& Instance()
	{
		if (!instance)
			instance = new Dockyard();
		return *instance;
	};

	// Methods Users need to override
    void Initialize() override;
    void LoadContent() override;
	void Update() override;
    void Draw() override;
    void UnLoadContent() override;

	// defined by user in Dockyard Resources, different for every game
	void LoadResources();
	void GameInitialize();
	void GameEnd();

	// called at the end of Run(), no static version needed
	void Delete();

	// for internal engine use only
	float PrivGetTimeInSeconds();
	static float GetTimeInSeconds() { return Instance().PrivGetTimeInSeconds(); };

	// private versions of static methods
	void PrivRun();
	int PrivGetWidth();
	int PrivGetHeight();
	void PrivSetWindowName(const char* name);
	void PrivSetWidthHeight(int w, int h);
	void PrivSetClear(float r, float g, float b, float a);

	friend class DockyardAttorney;

public:
	static void Run() { Instance().PrivRun(); }
	static int GetWidth() { return Instance().PrivGetWidth(); }
	static int GetHeight() { return Instance().PrivGetHeight(); }
	static void SetWindowName(const char* name) { Instance().PrivSetWindowName(name); }
	static void SetWidthHeight(int w, int h) { Instance().PrivSetWidthHeight(w, h); }
	static void SetClear(float r, float g, float b, float a) { Instance().PrivSetClear(r, g, b, a); }
};

#endif