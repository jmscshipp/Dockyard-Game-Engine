//#ifndef _SpriteString
//#define _SpriteString
//
////#include "SpriteFont.h"
//#include <list>
//
//// forward declaration
//class DockyardSprite;
//class SpriteFont;
//
//class SpriteString
//{
//public:
//	// big four
//	SpriteString();
//	SpriteString(SpriteFont* font, std::string s, int x, int y);
//	SpriteString(const SpriteString&) = delete;
//	SpriteString& operator = (const SpriteString&) = delete;
//	~SpriteString() = default;
//
//	// get
//	int GetHeight();
//	int GetWidth();
//	//set
//	void Set(int x, int y);
//	void Set(SpriteFont* font, std::string s, int x, int y);
//	void Render();
//
//private:
//	SpriteFont* sFont;
//	int posX, posY;
//	int width, height;
//
//	using Glyph = DockyardSprite;
//	using GlyphCollection = std::list<Glyph*>;
//	GlyphCollection glyphs;
//
//};
//
//#endif