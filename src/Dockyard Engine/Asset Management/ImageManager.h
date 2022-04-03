#ifndef _ImageManager
#define _ImageManager

#include "AzulCore.h"
#include <map>

class ImageManager
{
private:
	static ImageManager* instance; // set up as singleton

	// big four
	ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator = (const ImageManager&) = delete;
	~ImageManager();

	static ImageManager& Instance()
	{
		if (!instance)
			instance = new ImageManager();
		return *instance;
	};

	void PrivLoad(std::string imageName, Texture* tex);
	void PrivLoad(std::string imageName, Texture* tex, Rect* r);
	Image* PrivGetImage(std::string imageName);
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	// to allow Dockyard to Delete() singleton
	friend class ImageManagerAttorney;

	const std::string defaultPath = "Textures/"; // need to include '/' for file path
	std::map<std::string, Image*> loadedImages;

public:
	/// \brief Loads a specified texture as an image
	/// \ingroup ASSETMANAGEMENT 
	/// 	
	/// Adds the new image to the engine's collection of available to use images.	 
	/// If an image has already been loaded with the given name, this function will throw an error
	///  		 
	/// \param imageName	The name given to the image when it's loaded. This is what will be passed to ImageManager::GetImage to retrieve the image later
	/// \param tex	A pointer to the texture the image is being taken from
	/// 
	///  \par Example:
	/// Loading a texture as an image
	///		\code
	///		void Dockyard::LoadResources()
	///		{
	///			// loading an image from the previously loaded texture "MapTex" and calling it "Map"
	///			ImageManager::Load("Map", TextureManager::GetTexture("MapTex"));
	///		}
	///		\endcode
	/// \note The texture an image is loaded from most already be loaded using TextureManager::LoadTexture.
	/// In most cases, images should be loaded in Dockyard::LoadResources to be accessed elsewhere with ImageManager::GetImage
	static void Load(std::string imageName, Texture* tex) { Instance().PrivLoad(imageName, tex); }
	/// \brief Loads an image from a section of a specified texture, according to the dimensions of a specified rectangle
	/// \ingroup ASSETMANAGEMENT 
	/// 	
	/// Adds the new image to the engine's collection of available to use images.	 
	/// If an image has already been loaded with the given name, this function will throw an error
	///  		 
	/// \param imageName	The name given to the image when it's loaded. This is what will be passed to ImageManager::GetImage to retrieve the image later
	/// \param tex	A pointer to the texture the image is being taken from
	/// \param r A rectangle specifying the section of the texture that will be used for the image
	/// 
	///  \par Example:
	/// Loading a texture as an image
	///		\code
	///		void Dockyard::LoadResources()
	///		{
	///			// loading an image from a section of the previously loaded texture "SymbolsTex" and calling it "Arrow"
	///			// the Rect specifies the section of the texture being used
	///			// it has a width of 10, a height of 20, and is centered at the origin of the texture
	///			ImageManager::Load("Arrow", TextureManager::GetTexture("SymbolsTex"), new Rect(0, 0, 10, 20));
	///		}
	///		\endcode
	/// \note The texture an image is loaded from most already be loaded using TextureManager::LoadTexture.
	/// In most cases, images should be loaded in Dockyard::LoadResources to be accessed elsewhere with ImageManager::GetImage
	static void Load(std::string imageName, Texture* tex, Rect* r) { Instance().PrivLoad(imageName, tex, r); }
	/// \brief Retrieve previously loaded image by name
	/// \ingroup ASSETMANAGEMENT 
	/// 		 
	/// If an image with the specified name hasn't been loaded, this function will throw an error
	/// 
	/// \param imageName	The name of the image to be retrieved, which was given when the image was loaded
	/// 
	///  \par Example:
	/// Getting image to use with sprite GraphicsObject
	///		\code
	///		Map::Map()
	///		{
	///			Image* mapImage = ImageManager::GetImage("Map");
	///			gObjMap = new GraphicsObject_Sprite(ModelManager::GetModel("DefaultSpriteModel"), ShaderManager::GetShader("DefaultSpriteShader"), myImage, myImage->pImageRect);
	///		}
	///		\endcode
	/// \note images  most be loaded with ImageManager::LoadImage before being retrieved
	static Image* GetImage(std::string imageName) { return Instance().PrivGetImage(imageName); }
};

#endif

