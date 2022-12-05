#ifndef _TextureManager
#define _TextureManager

#include "GraphicsCore.h"
#include <map>

class TextureManager
{
private:
	static TextureManager* instance; // set up as singleton

	// big four
	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator = (const TextureManager&) = delete;
	~TextureManager();

	static TextureManager& Instance()
	{
		if (!instance)
			instance = new TextureManager();
		return *instance;
	};

	void PrivLoadTexture(std::string textureName, std::wstring textureFileLocation);
	//void PrivLoadTexture(std::string textureName, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char& alpha);
	Texture* PrivGetTexture(std::string textureName);
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	// to allow Dockyard to Delete() singleton
	friend class TextureManagerAttorney;

	const std::wstring defaultPath = L"../Assets/Textures/"; // need to include '/' for file path
	std::map<std::string, Texture*> loadedTextures;

public:
	/// \brief Loads a texture from from specified file location
	/// \ingroup ASSETMANAGEMENT 
	/// 	
	/// Adds the new texture to the engine's collection of available to use textures.	 
	/// If a texture has already been loaded with the given name, this function will throw an error
	/// 
	/// \param textureName	The name given to the texture when it's loaded. This is what will be passed to TextureManager::GetTexture to retrieve the texture later
	/// \param textureFileLocation	The name of the texture file located in Assets/Textures/ <b>including</b> the file extension
	/// 
	///  \par Example:
	/// Loading a texture from file
	///		\code
	///		void Dockyard::LoadResources()
	///		{
	///			// loading a new texture and calling it "House"
	///			TextureManager::LoadTexture("House", "HouseTex.tga");
	///		}
	///		\endcode
	/// \note The texture file being loaded must be in Targa (.tga) format to be loaded correctly.
	/// In most cases, textures should be loaded in Dockyard::LoadResources to be accessed elsewhere with TextureManager::GetTexture
	static void LoadTexture(std::string textureName, std::wstring textureFileLocation) { Instance().PrivLoadTexture(textureName, textureFileLocation); }
	/// \brief Loads a flat color texture with the specified rgba values
	/// \ingroup ASSETMANAGEMENT 
	/// 	
	/// Adds the new texture to the engine's collection of available to use textures.	 
	/// If a texture has already been loaded with the given name, this function will throw an error
	/// 	 
	/// \param textureName	The name given to the texture when it's loaded. This is what will be passed to TextureManager::GetTexture to retrieve the texture later
	/// \param red	How much of texture color is contributed from red, from 0 - 255
	/// \param green	How much of texture color is contributed from green, from 0 - 255
	/// \param blue	How much of texture color is contributed from blue, from 0 - 255
	/// \param alpha	Transparency of texture color, from 0 - 255
	/// 
	///  \par Example:
	/// Loading a texture from color
	///		\code
	///		void Dockyard::LoadResources()
	///		{
	///			// loading a new texture and calling it "BurntOrange"
	///			TextureManager::LoadTexture("BurntOrange", 237, 147, 82, 255);
	///		}
	///		\endcode
	/// \note In most cases, textures should be loaded in Dockyard::LoadResources to be accessed elsewhere with TextureManager::GetTexture
	// ACTIVATE HERE vv TO ADD BACK IN LOAD TEXTURE FROM COLOR ///////////////////
	////////////////////////static void LoadTexture(std::string textureName, const unsigned char&red, const unsigned char& green, const unsigned char& blue, const unsigned char& alpha) { Instance().PrivLoadTexture(textureName, red, green, blue, alpha); }
	/// \brief Retrieve previously loaded texture by name
	/// \ingroup ASSETMANAGEMENT 
	/// 		 
	/// If a texture with the specified name hasn't been loaded, this function will throw an error
	/// 
	/// \param textureName	The name of the texture to be retrieved, which was given when the texture was loaded
	/// 
	///  \par Example:
	/// Getting textures to use with GraphicsObjects
	///		\code
	///		BackgroundProps::BackgroundProps()
	///		{
	///			// creating textured GraphicsObject with lighting
	///			Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	///			Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	///			gObjHouse = new GraphicsObject_TextureLight(ModelManager::GetModel("House"), ShaderManager::GetShader("TextureLight"), TextureManager::GetTexture("House"), LightColor, LightPos);
	///			
	///			// creating textured GraphicsObject without lighting (flat)
	///			gObjSun = new GraphicsObject_TextureFlat(ModelManager::GetModel("Sun"), ShaderManager::GetShader("Texture"), TextureManager::GetTexture("BurntOrange"));
	///		}
	///		\endcode
	/// \note Textures most be loaded with TextureManager::LoadTexture before being retrieved
	static Texture* GetTexture(std::string textureName) { return Instance().PrivGetTexture(textureName); }
};

#endif