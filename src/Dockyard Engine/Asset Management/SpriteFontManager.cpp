//#include "SpriteFontManager.h"
//#include "SpriteFont.h"
//
//SpriteFontManager* SpriteFontManager::instance = nullptr;
//
//SpriteFontManager::SpriteFontManager()
//{
//	SpriteFont* newLoadedFont = new SpriteFont("DefaultFont", (defaultPath + "adobefont").c_str());
//	loadedFonts.emplace("DefaultFont", newLoadedFont);
//}
//
//SpriteFontManager::~SpriteFontManager()
//{
//	for (std::pair<std::string, SpriteFont*> element : loadedFonts)
//		delete(element.second);
//}
//
//void SpriteFontManager::PrivLoadSpriteFont(std::string fontName, std::string fontFileLocation)
//{
//	if (loadedFonts.count(fontName) > 0) // if a texture with this name has already been loaded
//	{
//		// THROW ERROR
//		throw("!!! ERROR: There is already a loaded font named " + fontName + " !!!\n");
//	}
//	else
//	{
//		SpriteFont* newLoadedFont = new SpriteFont(fontName, (defaultPath + fontFileLocation).c_str());
//		loadedFonts.emplace(fontName, newLoadedFont);
//	}
//}
//
//SpriteFont* SpriteFontManager::PrivGetSpriteFont(std::string fontName)
//{
//	std::map<std::string, SpriteFont*>::const_iterator findResult = loadedFonts.find(fontName);
//	if (findResult == loadedFonts.end()) // if we have no texture of this name loaded
//	{
//		// THROW ERROR
//		throw("!!! ERROR: There is no loaded font named " + fontName + " !!!\n");
//		return nullptr;
//	}
//	else
//	{
//		return findResult->second;
//	}
//}
//
//void SpriteFontManager::NonstaticDelete()
//{
//	delete instance;
//	instance = nullptr;
//}