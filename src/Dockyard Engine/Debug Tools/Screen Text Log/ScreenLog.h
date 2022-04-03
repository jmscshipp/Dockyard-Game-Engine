#ifndef _ScreenLog
#define _ScreenLog

#include <list>

// forward declaration
class SpriteFont;
class SpriteString;

class ScreenLog
{
private:
	static ScreenLog* instance; // set up as singleton

	// big four
	ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator = (const ScreenLog&) = delete;
	~ScreenLog();

	static ScreenLog& Instance()
	{
		if (!instance)
			instance = new ScreenLog();
		return *instance;
	};

	using Message = SpriteString*;
	using MessageCollection = std::list<Message>;

	// private versions of public methods
	void PrivSetAnchor(int x, int y);
	void PrivSetFont(SpriteFont* newFont);
	// called by dockyard through attorney
	void NonstaticRender();
	static void Render() { Instance().NonstaticRender(); }
	// helper function
	void AddToCollection(const std::string& s);
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	// to allow Dockyard to Delete() singleton and Render()
	friend class ScreenLogAttorney;

	int anchorX;
	int anchorY;
	int originalAnchorY; // to keep when moving anchor for each new line
	SpriteFont* font;
	MessageCollection messages;
	static char debugBuffer[256];

public:
	static void Add(char* A, ...);
	static void SetAnchor(int x, int y) { Instance().PrivSetAnchor(x, y); }
	static void SetFont(SpriteFont* newFont) { Instance().PrivSetFont(newFont); }
};

#endif