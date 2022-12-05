//#ifndef _SpriteFontManager
//#define _SpriteFontManager
//
//#include <map>
//
//// forward declaration 
//class SpriteFont;
//
//class SpriteFontManager
//{
//private:
//	static SpriteFontManager* instance; // set up as singleton
//
//	// big four
//	SpriteFontManager();
//	SpriteFontManager(const SpriteFontManager&) = delete;
//	SpriteFontManager& operator = (const SpriteFontManager&) = delete;
//	~SpriteFontManager();
//
//	static SpriteFontManager& Instance()
//	{
//		if (!instance)
//			instance = new SpriteFontManager();
//		return *instance;
//	};
//
//	void PrivLoadSpriteFont(std::string fontName, std::string fontFileLocation);
//	SpriteFont* PrivGetSpriteFont(std::string fontName);
//	void NonstaticDelete();
//	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made
//
//	// to allow Dockyard to Delete() singleton
//	friend class SpriteFontManagerAttorney;
//
//	const std::string defaultPath = "../Assets/Fonts/"; // need to include '/' for file path
//	std::map<std::string, SpriteFont*> loadedFonts;
//
//public:
//	/// \brief Loads a font from from specified file location
//	/// \ingroup ASSETMANAGEMENT 
//	/// 	
//	/// Adds the new font to the engine's collection of available to use fonts.	 
//	/// If a font has already been loaded with the given name, this function will throw an error
//	///  	 
//	/// \param fontName	The name given to the font when it's loaded. This is what will be passed to FontManager::GetSpriteFont to retrieve the font later
//	/// \param fontFileLocation	The name of the font file located in Assets/Fonts/ <b>excluding</b> the file extension
//	/// 
//	///  \par Example:
//	/// Loading a font from file
//	///		\code
//	///		void Dockyard::LoadResources()
//	///		{
//	///			// loading a new font and calling it "Helvetica"
//	///			SpriteFontManager::LoadSpriteFont("Helvetica", "HelveticaFont");
//	///		}
//	///		\endcode
//	/// \note The font file being loaded must be in XML (.xml) format to be loaded correctly.
//	/// In most cases, fonts should be loaded in Dockyard::LoadResources to be accessed elsewhere with SpriteFontManager::GetSpriteFont
//	static void LoadSpriteFont(std::string fontName, std::string fontFileLocation) { Instance().PrivLoadSpriteFont(fontName, fontFileLocation); }
//	/// \brief Retrieve previously loaded font by name
//	/// \ingroup ASSETMANAGEMENT 
//	/// 		 
//	/// If a font with the specified name hasn't been loaded, this function will throw an error
//	/// 
//	/// \param fontName	The name of the font to be retrieved, which was given when the font was loaded
//	/// 
//	///  \par Example:
//	/// Getting font to use with SpriteString
//	///		\code
//	///		TextBubble::TextBubble(std::string sentence, int xPos, int yPos)
//	///		{
//	///			font = SpriteFontManager::GetSpriteFont("Helvetica");
//	///			str = new SpriteString(font, sentence, x, y);
//	///		}
//	///		\endcode
//	/// \note fonts most be loaded with SpriteFontManager::LoadSpriteFont before being retrieved
//	static SpriteFont* GetSpriteFont(std::string fontName) { return Instance().PrivGetSpriteFont(fontName); }
//};
//
//#endif