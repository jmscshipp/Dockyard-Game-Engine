//#include "SpriteString.h"
//#include "SpriteFont.h"
//#include "DockyardSprite.h"
//#include "SceneManager.h"
//#include "Scene.h"
//#include "SpriteFontManager.h"
//
//SpriteString::SpriteString()
//	:sFont(SpriteFontManager::GetSpriteFont("DefaultFont")),
//	posX(0),
//	posY(0),
//	width(0),
//	height(static_cast<int>(sFont->GetGlyph(32)->GetHeight()))
//{
//}
//
//SpriteString::SpriteString(SpriteFont* font, std::string s, int x, int y)
//	:sFont(font),
//	posX(x),
//	posY(y),
//	width(0),
//	height(static_cast<int>(font->GetGlyph(32)->GetHeight()))
//{
//	for (char& c : s)
//	{
//		// get specified glyph from font
//		Glyph* newGlyph = sFont->GetGlyph(c);
//		// add to glyph list
//		glyphs.push_back(newGlyph);
//		// update total width of string
//		width += static_cast<int>(newGlyph->GetWidth());
//	}
//}
//
//int SpriteString::GetHeight()
//{
//	return height;
//}
//
//int SpriteString::GetWidth()
//{
//	return width;
//}
//
//void SpriteString::Set(int x, int y)
//{
//	posX = x;
//	posY = y;
//}
//
//void SpriteString::Set(SpriteFont* font, std::string s, int x, int y)
//{
//	glyphs.clear();
//	sFont = font;
//	posX = x;
//	posY = y;
//	width = 0;
//	height = static_cast<int>(font->GetGlyph(32)->GetHeight());
//
//	for (char& c : s)
//	{
//		// get specified glyph from font
//		Glyph* newGlyph = sFont->GetGlyph(c);
//		// add to glyph list
//		glyphs.push_back(newGlyph);
//		// update total width of string
//		width += static_cast<int>(newGlyph->GetWidth());
//	}
//}
//
//void SpriteString::Render()
//{
//	float offset = 0;
//
//	for (Glyph* g : glyphs)
//	{
//		g->SetPosition(static_cast<float>(posX + offset), static_cast<float>(posY));
//		g->Render(SceneManager::GetCurrentScene()->GetDefaultOrthoCam());
//		// update offset for next character
//		offset += g->GetWidth();
//	}
//}