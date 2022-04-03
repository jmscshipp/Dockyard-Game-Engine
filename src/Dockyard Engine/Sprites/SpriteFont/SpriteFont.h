#ifndef _SpriteFont
#define _SpriteFont

#include <map>
#include <xmllite.h>

// forward declaration
class Texture;
class DockyardSprite;

class SpriteFont
{
public:
	SpriteFont() = delete;
	SpriteFont(std::string fontName, std::string path);
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;

	using Key = int;
	using Glyph = DockyardSprite;

	Glyph* GetGlyph(char c);

private:
	std::string name;
	Texture* fontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);
};

#endif