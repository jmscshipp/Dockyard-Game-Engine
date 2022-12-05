#ifndef _Dockyard
#define _Dockyard

// forward declaration
class Vect;

class Dockyard
{
private:
	static Dockyard* instance; // set up as singleton

	// big four
	Dockyard() = default;
	Dockyard(const Dockyard&) = delete;
	Dockyard& operator = (const Dockyard&) = delete;
	~Dockyard(); // unload content

	static Dockyard& Instance()
	{
		if (!instance)
			instance = new Dockyard();
		return *instance;
	};

	// big engine functions
    void NonstaticInitialize(HWND hwnd);
	void NonstaticUpdate();
    void NonstaticDraw();
	void NonstaticDelete(); // delete Dockyard

	// static versions
	static void Initialize(HWND hwnd) { Instance().NonstaticInitialize(hwnd); };
	static void Update() { Instance().NonstaticUpdate(); };
	static void Draw() { Instance().NonstaticDraw(); };
	static void Delete() { Instance().NonstaticDelete(); };

	// defined by user in Dockyard Resources, different for every game
	void LoadResources();
	void GameInitialize();
	void GameEnd();

	// private versions of static methods
	int PrivGetWidth();
	int PrivGetHeight();
	void PrivSetWindowName(const char* name);
	void PrivSetWidthHeight(int w, int h);
	void PrivSetBackgroundColor(const Vect& color);

	friend class DockyardAttorney;
	friend class WindowController;

public:
	static int GetWidth() { return Instance().PrivGetWidth(); }
	static int GetHeight() { return Instance().PrivGetHeight(); }
	static void SetWindowName(const char* name) { Instance().PrivSetWindowName(name); }
	static void SetWidthHeight(int w, int h) { Instance().PrivSetWidthHeight(w, h); }
	static void SetBackgroundColor(const Vect& color) { Instance().PrivSetBackgroundColor(color); }
};

#endif